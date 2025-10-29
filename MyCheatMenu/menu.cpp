#include "menu.h"
#include "themes.h"
#include <cstdio>  // For printf

// Define globals
WeaveUI::Legit WeaveUI::legit;
WeaveUI::Rage WeaveUI::rage;
WeaveUI::Visuals WeaveUI::visuals;
WeaveUI::Config WeaveUI::config;

void WeaveUI::RenderMenu() {
    Themes::ApplyRagnarokTheme();

    if (!config.show_menu) return;

    ImGui::SetNextWindowSize(ImVec2(850, 650), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);

    if (!ImGui::Begin("Weave V3 - RAGNAREK Edition", &config.show_menu, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize)) {
        ImGui::End();
        return;
    }

    // Header with neon title
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.54f, 0.00f, 1.00f, 1.00f));  // Neon purple
    ImGui::Text("Weave V3"); ImGui::SameLine();
    ImGui::PopStyleColor();
    ImGui::TextDisabled("| RAGNAREK Build v2.0");
    ImGui::SameLine(ImGui::GetWindowWidth() - 100.0f);
    if (ImGui::Button("Unload", ImVec2(80, 24))) config.show_menu = false;

    ImGui::Separator(); ImGui::Spacing();

    // Tabs with purple active
    if (ImGui::BeginTabBar("MainTabs", ImGuiTabBarFlags_None)) {
        if (ImGui::BeginTabItem(" Legit  ")) { config.active_tab = 0; ImGui::EndTabItem(); }
        if (ImGui::BeginTabItem(" Rage   ")) { config.active_tab = 1; ImGui::EndTabItem(); }
        if (ImGui::BeginTabItem(" Visuals")) { config.active_tab = 2; ImGui::EndTabItem(); }
        if (ImGui::BeginTabItem(" Config ")) { config.active_tab = 3; ImGui::EndTabItem(); }
        if (ImGui::BeginTabItem(" Misc   ")) { config.active_tab = 4; ImGui::EndTabItem(); }
        ImGui::EndTabBar();
    }

    ImGui::Spacing(); ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(12, 8));

    // Legit Tab — Multi-column, grouped (RAGNAREK style)
    if (config.active_tab == 0) {
        ImGui::Columns(2, "LegitCols", false);
        ImGui::SetColumnWidth(0, 200);

        // Group: Aimbot (with "icon" text)
        ImGui::TextColored(ImVec4(0.54f, 0.00f, 1.00f, 1.0f), "🎯 Aimbot");
        ImGui::Checkbox("Enable", &legit.aimbot);
        ImGui::Checkbox("RCS", &legit.rcs);

        // Group: Trigger
        ImGui::TextColored(ImVec4(0.54f, 0.00f, 1.00f, 1.0f), "🔫 Trigger");
        ImGui::Checkbox("Enable", &legit.triggerbot);

        ImGui::NextColumn();

        // Settings Group
        ImGui::TextColored(ImVec4(0.54f, 0.00f, 1.00f, 1.0f), "⚙️ Settings");
        ImGui::SliderFloat("FOV", &legit.fov, 1.0f, 180.0f, "%.0f");
        ImGui::SliderInt("Smooth", &legit.smooth, 1, 20, "%d");

        const char* hitboxes[] = { "Head", "Chest", "Stomach", "Feet", "Closest" };
        ImGui::Combo("Hitbox", &legit.hitbox, hitboxes, IM_ARRAYSIZE(hitboxes));

        ImGui::Columns(1);
        ImGui::Separator();
        if (ImGui::Button("Apply Legit", ImVec2(160, 28))) {
            printf("Aimbot Applied: FOV=%.0f, Smooth=%d, Hitbox=%s\n", legit.fov, legit.smooth, hitboxes[legit.hitbox]);
        }
    }

    // Rage Tab — Toggles + big button
    if (config.active_tab == 1) {
        ImGui::Checkbox("Ragebot", &rage.rage);
        ImGui::Checkbox("Anti-Aim", &rage.antiaim);
        ImGui::Checkbox("Fake Lag", &rage.fakelag);
        ImGui::Separator();
        if (ImGui::Button("Activate Rage Mode", ImVec2(140, 32))) {
            printf("RAGE ACTIVATED!\n");
        }
    }

    // Visuals Tab — Checkboxes + color picker
    if (config.active_tab == 2) {
        ImGui::Checkbox("ESP Box", &visuals.esp);
        ImGui::Checkbox("Chams", &visuals.chams);
        ImGui::Checkbox("Glow", &visuals.glow);
        ImGui::Separator();
        ImGui::ColorEdit3("Box Color", (float*)&visuals.box_color);
        ImGui::Separator();
        if (ImGui::Button("Update Visuals", ImVec2(120, 28))) {
            printf("Visuals Updated: ESP=%s, Color=RGB(%.0f,%.0f,%.0f)\n", visuals.esp ? "ON" : "OFF", visuals.box_color.x * 255, visuals.box_color.y * 255, visuals.box_color.z * 255);
        }
    }

    // Config Tab — Buttons + theme switch
    if (config.active_tab == 3) {
        ImGui::TextColored(ImVec4(0.54f, 0.00f, 1.00f, 1.0f), "💾 Config Manager");
        if (ImGui::Button("Save JSON", ImVec2(100, 28))) { /* Implement JSON save */ }
        ImGui::SameLine();
        if (ImGui::Button("Load JSON", ImVec2(100, 28))) { /* Implement JSON load */ }
        ImGui::Separator();
        static int theme_idx = 0;
        const char* themes[] = { "RAGNAREK Neon", "Classic Dark", "Glass Morph" };
        ImGui::Combo("Theme", &theme_idx, themes, IM_ARRAYSIZE(themes));
        if (ImGui::Button("Apply Theme", ImVec2(120, 28))) { Themes::ApplyRagnarokTheme(); }
    }

    // Misc Tab — Panic + status
    if (config.active_tab == 4) {
        ImGui::TextColored(ImVec4(0.54f, 0.00f, 1.00f, 1.0f), "🛡️ Misc");
        if (ImGui::Button("Panic Key (F8)", ImVec2(120, 28))) config.show_menu = false;
        ImGui::Text("Status: Injected | Toggle: INSERT");
    }

    ImGui::PopStyleVar();
    ImGui::End();
}