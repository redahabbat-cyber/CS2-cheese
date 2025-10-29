// main.cpp – 100% WORKING FROM PUBLIC REPOS (MitilcC + R1ddles)
#include <windows.h>
#include <thread>
#include <chrono>

#include <d3d11.h>
#include <dxgi.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "kiero.h"

#include "globals.h"
#include "offsets.h"
#include "menu.h"

// GLOBALS
HWND g_hwnd = nullptr;
ID3D11Device* g_pd3dDevice = nullptr;
ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
bool g_showMenu = false;
bool g_initialized = false;
bool g_running = true;

// PRESENT HOOK
typedef HRESULT(__stdcall* Present_t)(IDXGISwapChain*, UINT, UINT);
Present_t oPresent = nullptr;

HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    static bool init = false;  // INIT GUARD (from MitilcC)
    if (!init)
    {
        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&g_pd3dDevice)))
        {
            g_pd3dDevice->GetImmediateContext(&g_pd3dDeviceContext);

            DXGI_SWAP_CHAIN_DESC sd{};
            pSwapChain->GetDesc(&sd);
            g_hwnd = sd.OutputWindow;

            // FALLBACK HWND (from R1ddles)
            if (!g_hwnd || !IsWindow(g_hwnd))
                g_hwnd = FindWindowA("Valve001", nullptr);

            if (!g_hwnd) return oPresent(pSwapChain, SyncInterval, Flags);

            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
            io.IniFilename = nullptr;
            io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;  // FIX CURSOR (from gmh5225)

            ImGui_ImplWin32_Init(g_hwnd);
            ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
            ImGui::StyleColorsDark();

            init = true;
            g_initialized = true;
        }
        else
        {
            return oPresent(pSwapChain, SyncInterval, Flags);
        }
    }

    if (!g_initialized) return oPresent(pSwapChain, SyncInterval, Flags);

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // TOGGLE (from all repos: &1 for edge)
    if (GetAsyncKeyState(VK_INSERT) & 1)
        g_showMenu = !g_showMenu;

    if (g_showMenu)
        RenderMenu();

    ImGui::EndFrame();  // REQUIRED (from Guided Hacking)
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    return oPresent(pSwapChain, SyncInterval, Flags);
}

// SETUP (KIERO BIND 8)
void SetupHooks()
{
    if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
    {
        kiero::bind(8, (void**)&oPresent, hkPresent);  // INDEX 8 (Present, from all CS2 repos)
    }
}

// CLEANUP
void Cleanup()
{
    kiero::shutdown();
    if (g_pd3dDeviceContext) g_pd3dDeviceContext->Release();
    if (g_pd3dDevice) g_pd3dDevice->Release();
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

// THREAD (WAIT FOR CLIENT.DLL + SLEEP)
void CheatThread(HMODULE hModule)
{
    while (!GetModuleHandleA("client.dll"))
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

    std::this_thread::sleep_for(std::chrono::seconds(2));  // EXTRA WAIT (from KisSsArt)

    SetupHooks();

    while (g_running)
    {
        if (GetAsyncKeyState(VK_END) & 1)
            g_running = false;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    Cleanup();
    FreeLibraryAndExitThread(hModule, 0);
}

// DLLMAIN
BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)CheatThread, hModule, 0, nullptr);
    }
    return TRUE;
}