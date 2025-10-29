// main.cpp
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Psapi.h>
#include <d3d11.h>
#include <dxgi.h>
#include <thread>
#include <chrono>

#include "kiero.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include "menu.h"
#include "themes.h"
#include "offsets.h"
#include "globals.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "libMinHook.x64.lib")
#pragma comment(lib, "Psapi.lib")

static ID3D11Device*            g_pd3dDevice = nullptr;
static ID3D11DeviceContext*     g_pd3dDeviceContext = nullptr;
static IDXGISwapChain*          g_pSwapChain = nullptr;
static ID3D11RenderTargetView*  g_mainRenderTargetView = nullptr;
static HWND                     g_hWnd = nullptr;

template<typename T> T RPM(uintptr_t addr) {
    T v{}; ReadProcessMemory(g_hProcess, (LPCVOID)addr, &v, sizeof(T), nullptr); return v;
}

bool AttachToCS2() {
    HWND hwnd = FindWindowA(nullptr, "Counter-Strike 2");
    if (!hwnd) return false;
    GetWindowThreadProcessId(hwnd, &g_pid);
    g_hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, g_pid);
    if (!g_hProcess) return false;

    HMODULE hMod = nullptr;
    DWORD cb;
    if (EnumProcessModules(g_hProcess, &hMod, sizeof(hMod), &cb)) {
        char name[MAX_PATH];
        if (GetModuleFileNameExA(g_hProcess, hMod, name, MAX_PATH) && strstr(name, "client.dll")) {
            g_clientBase = (uintptr_t)hMod;
            return true;
        }
    }
    return false;
}

typedef HRESULT(__stdcall* PresentFn)(IDXGISwapChain*, UINT, UINT);
static PresentFn oPresent = nullptr;

HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
    static bool init = false;
    if (!init) {
        pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&g_pd3dDevice);
        g_pd3dDevice->GetImmediateContext(&g_pd3dDeviceContext);
        DXGI_SWAP_CHAIN_DESC sd; pSwapChain->GetDesc(&sd);
        g_hWnd = sd.OutputWindow;
        g_pSwapChain = pSwapChain;

        ID3D11Texture2D* bb;
        pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&bb);
        g_pd3dDevice->CreateRenderTargetView(bb, nullptr, &g_mainRenderTargetView);
        bb->Release();

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        Theme::Dark();
        ImGui_ImplWin32_Init(g_hWnd);
        ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
        init = true;
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    static bool attached = false;
    if (!attached) attached = AttachToCS2();

    if (attached && g_clientBase) {
        auto lp = RPM<uintptr_t>(g_clientBase + offsets::dwLocalPlayerPawn);
        if (lp) {
            int hp = RPM<int>(lp + offsets::m_iHealth);
            ImGui::Begin("Debug");
            ImGui::Text("Health: %d", hp);
            ImGui::End();
        }
    }

    if (GetAsyncKeyState(VK_INSERT) & 1) Menu::show = !Menu::show;
    Menu::Render();

    ImGui::Render();
    g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    return oPresent(pSwapChain, SyncInterval, Flags);
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    while (!FindWindowA(nullptr, "Counter-Strike 2"))
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

    if (kiero::init(kiero::RenderType::D3D11) != kiero::Status::Success)
        return 1;

    kiero::bind(8, (void**)&oPresent, hkPresent);

    MSG msg{};
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    kiero::shutdown();
    if (g_hProcess) CloseHandle(g_hProcess);
    return 0;
}
