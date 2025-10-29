// menu.cpp
#include <Windows.h>
#include "menu.h"
#include "themes.h"
#include "globals.h"

void Menu::Render()
{
    if (!show) return;

    ImGui::Begin("CS2 Cheese", &show, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar()) {
        if (ImGui::MenuItem("Unload")) ExitProcess(0);
        ImGui::EndMenuBar();
    }

    ImGui::Text("Status: %s", g_hProcess ? "Attached" : "Waiting...");
    ImGui::Separator();
    ImGui::Checkbox("Bunny Hop", &bhop);
    ImGui::Checkbox("ESP", &esp);
    ImGui::Checkbox("Glow", &glow);
    if (ImGui::Button("Panic")) ExitProcess(0);
    ImGui::End();
}
