// themes.cpp - RAGNAREK v3 "CYBERFIRE" THEME
#include "themes.h"

void Themes::ApplyRagnarokTheme() {
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 8.0f;
    style.ChildRounding = 8.0f;
    style.FrameRounding = 6.0f;
    style.PopupRounding = 6.0f;
    style.TabRounding = 6.0f;
    style.ScrollbarRounding = 12.0f;
    style.GrabRounding = 6.0f;
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.FramePadding = ImVec2(12, 8);
    style.ItemSpacing = ImVec2(14, 10);
    style.ItemInnerSpacing = ImVec2(8, 8);
    style.IndentSpacing = 28.0f;
    style.ScaleAllSizes(1.15f);  // Bigger, bolder

    ImVec4* colors = style.Colors;

    // === DEEP VOID BACKGROUND ===
    colors[ImGuiCol_WindowBg] = ImVec4(0.03f, 0.03f, 0.05f, 0.98f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.05f, 0.05f, 0.08f, 0.98f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.04f, 0.04f, 0.06f, 0.95f);

    // === NEON CYAN + PURPLE ACCENTS ===
    ImVec4 neon_purple = ImVec4(0.60f, 0.00f, 1.00f, 1.00f);  // #9900FF
    ImVec4 neon_cyan = ImVec4(0.00f, 0.95f, 1.00f, 1.00f);  // #00F2FF
    ImVec4 fire_orange = ImVec4(1.00f, 0.40f, 0.00f, 1.00f);

    colors[ImGuiCol_CheckMark] = neon_purple;
    colors[ImGuiCol_SliderGrab] = neon_cyan;
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.20f, 1.00f, 1.00f, 1.00f);

    // === BIG GLOWING BUTTONS ===
    colors[ImGuiCol_Button] = ImVec4(0.12f, 0.12f, 0.18f, 0.70f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.60f, 0.00f, 1.00f, 0.40f);  // Purple glow
    colors[ImGuiCol_ButtonActive] = ImVec4(0.80f, 0.20f, 1.00f, 0.80f);  // Bright pulse

    // === TABS — ACTIVE GLOW ===
    colors[ImGuiCol_Tab] = ImVec4(0.10f, 0.10f, 0.16f, 0.80f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.60f, 0.00f, 1.00f, 0.60f);
    colors[ImGuiCol_TabActive] = ImVec4(0.70f, 0.10f, 1.00f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.08f, 0.08f, 0.12f, 0.97f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.25f, 0.25f, 0.35f, 1.00f);

    // === HEADERS & TEXT ===
    colors[ImGuiCol_Header] = ImVec4(0.60f, 0.00f, 1.00f, 0.35f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.60f, 0.00f, 1.00f, 0.85f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.80f, 0.20f, 1.00f, 1.00f);

    colors[ImGuiCol_Text] = ImVec4(0.98f, 0.98f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.60f, 1.00f);

    // === SEPARATORS & BORDERS ===
    colors[ImGuiCol_Separator] = ImVec4(0.60f, 0.00f, 1.00f, 0.50f);
    colors[ImGuiCol_Border] = ImVec4(0.40f, 0.40f, 0.50f, 0.50f);

    // === TITLE BAR ===
    colors[ImGuiCol_TitleBg] = ImVec4(0.02f, 0.02f, 0.03f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.10f, 0.00f, 0.20f, 1.00f);

    // === SCROLLBAR ===
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.30f, 0.30f, 0.40f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = neon_cyan;
}