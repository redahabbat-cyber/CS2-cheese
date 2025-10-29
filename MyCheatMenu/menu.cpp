#include "menu.h"
#include "themes.h"
#include <cstdio>
#include <windows.h>

WeaveUI::Legit    WeaveUI::legit;
WeaveUI::Rage     WeaveUI::rage;
WeaveUI::Visuals  WeaveUI::visuals;
WeaveUI::Config   WeaveUI::config;

void WeaveUI::InitMenu() {
    Themes::ApplyRagnarokTheme();
    config.show_menu = true;
}

void WeaveUI::RenderMenu() {
    if (GetAsyncKeyState(VK_INSERT) & 1) config.show_menu = !config.show_menu;
    if (!config.show_menu) return;

    ImGui::SetNextWindowSize(ImVec2(920, 720), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(60, 60), ImGuiCond_FirstUseEver);

    if (!ImGui::Begin("WEAVE V3 - CYBERFIRE", &config.show_menu,
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize)) {
        ImGui::End();
        return;
    }

    // === HEADER ===
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]); // Use default or custom bold font
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.00f, 0.95f, 1.00f, 1.00f));
    ImGui::Text("WEAVE V3"); ImGui::SameLine();
    ImGui::PopStyleColor();
    ImGui::TextDisabled(" | CYBERFIRE v3.0");
    ImGui::SameLine(ImGui::GetWindowWidth() - 120);
    if (ImGui::Button("EXIT", ImVec2(90, 32))) config.show_menu = false;
    ImGui::PopFont();

    ImGui::Separator(); ImGui::Spacing();

    // === TABS ===
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10, 8));
    if (ImGui::BeginTabBar("CyberTabs", ImGuiTabBarFlags_None)) {
        if (ImGui::BeginTabItem("  LEGIT  ")) { config.active_tab = 0; ImGui::EndTabItem(); }
        if (ImGui::BeginTabItem("  RAGE   ")) { config.active_tab = 1; ImGui::EndTabItem(); }
        if (ImGui::BeginTabItem("  VISUALS")) { config.active_tab = 2; ImGui::EndTabItem(); }
        if (ImGui::BeginTabItem("  CONFIG ")) { config.active_tab = 3; ImGui::EndTabItem(); }
        if (ImGui::BeginTabItem("  MISC   ")) { config.active_tab = 4; ImGui::EndTabItem(); }
        ImGui::EndTabBar();
    }
    ImGui::PopStyleVar();

    ImGui::Spacing(); ImGui::Spacing();

    // === CONTENT ===
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(16, 12));

    if (config.active_tab == 0) {
        ImGui::Columns(2, nullptr, false);
        ImGui::SetColumnWidth(0, 260);

        // Aimbot Group
        ImGui::TextColored(ImVec4(0.60f, 0.00f, 1.00f, 1.0f), "AIMBOT");
        ImGui::Checkbox("Enable##Aimbot", &legit.aimbot);
        ImGui::Checkbox("RCS", &legit.rcs);

        ImGui::Spacing();
        ImGui::TextColored(ImVec4(0.00f, 0.95f, 1.00f, 1.0f), "TRIGGERBOT");
        ImGui::Checkbox("Enable##Trigger", &legit.triggerbot);

        ImGui::NextColumn();

        ImGui::TextColored(ImVec4(1.00f, 0.40f, 0.00f, 1.0f), "SETTINGS");
        ImGui::SliderFloat("FOV", &legit.fov, 1.0f, 180.0f, "%.0f°");
        ImGui::SliderInt("Smooth", &legit.smooth, 1, 30, "%d");

        const char* hitboxes[] = { "Head", "Chest", "Stomach", "Pelvis", "Feet" };
        ImGui::Combo("Hitbox", &legit.hitbox, hitboxes, IM_ARRAYSIZE(hitboxes));

        ImGui::Columns(1);
        ImGui::Separator();
        if (ImGui::Button("APPLY LEGIT", ImVec2(200, 42))) {
            printf("[CYBERFIRE] Aimbot: FOV=%.0f Smooth=%d Hitbox=%s\n",
                legit.fov, legit.smooth, hitboxes[legit.hitbox]);
        }
    }

    if (config.active_tab == 1) {
        ImGui::Checkbox("Ragebot", &rage.rage);
        ImGui::Checkbox("Anti-Aim", &rage.antiaim);
        ImGui::Checkbox("Fake Lag", &rage.fakelag);
        ImGui::Separator();
        if (ImGui::Button("ACTIVATE RAGE", ImVec2(220, 48))) {
            printf("[CYBERFIRE] RAGE MODE ENGAGED!\n");
        }
    }

    if (config.active_tab == 2) {
        ImGui::Checkbox("ESP Box", &visuals.esp);
        ImGui::Checkbox("Chams", &visuals.chams);
        ImGui::Checkbox("Glow", &visuals.glow);
        ImGui::Separator();
        ImGui::ColorEdit3("Box Color", (float*)&visuals.box_color);
        ImGui::Separator();
        if (ImGui::Button("UPDATE VISUALS", ImVec2(180, 40))) {
            printf("[CYBERFIRE] Visuals Updated\n");
        }
    }

    if (config.active_tab == 3) {
        ImGui::TextColored(ImVec4(0.60f, 0.00f, 1.00f, 1.0f), "CONFIG SYSTEM");
        if (ImGui::Button("SAVE CONFIG", ImVec2(130, 40))) { /* TODO */ }
        ImGui::SameLine();
        if (ImGui::Button("LOAD CONFIG", ImVec2(130, 40))) { /* TODO */ }
        ImGui::Separator();
        if (ImGui::Button("RELOAD THEME", ImVec2(180, 40))) {
            Themes::ApplyRagnarokTheme();
        }
    }

    if (config.active_tab == 4) {
        ImGui::TextColored(ImVec4(1.00f, 0.40f, 0.00f, 1.0f), "MISC");
        if (ImGui::Button("PANIC (F8)", ImVec2(150, 40))) config.show_menu = false;
        ImGui::Text("Status: CYBERFIRE ACTIVE | Toggle: INSERT");
    }

    ImGui::PopStyleVar();
    ImGui::End();
}