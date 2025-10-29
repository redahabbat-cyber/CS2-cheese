#include <windows.h>
#include "imgui.h"
#include "globals.h"
#include "offsets.h"
#include "menu.h"

void RenderMenu()
{
    ImGui::Begin("CS2 Cheese v1.0", &g_showMenu, ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("Status: Injected & Running");
    ImGui::Separator();

    if (g_localPlayer)
    {
        int health = *(int*)((uintptr_t)g_localPlayer + offsets::m_iHealth);
        ImGui::Text("Health: %d", health);
    }
    else
    {
        ImGui::Text("Health: N/A (not in game)");
    }

    ImGui::Separator();
    ImGui::Text("Features (add in main.cpp):");
    ImGui::BulletText("Aimbot");
    ImGui::BulletText("ESP");
    ImGui::BulletText("Triggerbot");

    ImGui::Separator();
    if (ImGui::Button("Unload Cheat (END key)"))
        g_running = false;  // ← NOW RECOGNIZED

    ImGui::End();
}