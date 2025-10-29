#include "themes.h"

// RAGNAREK-v2 Theme: Deep black, neon purple (#8B00FF), subtle gradients, rounded (6px), glow hovers
void Themes::ApplyRagnarokTheme() {
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 6.0f;  // Rounded windows
    style.ChildRounding = 6.0f;
    style.FrameRounding = 6.0f;
    style.PopupRounding = 6.0f;
    style.TabRounding = 6.0f;  // Rounded tabs
    style.ScrollbarRounding = 12.0f;
    style.GrabRounding = 6.0f;
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.FramePadding = ImVec2(10, 6);
    style.ItemSpacing = ImVec2(12, 8);
    style.ItemInnerSpacing = ImVec2(6, 6);
    style.IndentSpacing = 25.0f;
    style.ScaleAllSizes(1.1f);  // Slight upscale for modern feel

    ImVec4* colors = style.Colors;
    // Deep black base
    colors[ImGuiCol_WindowBg] = ImVec4(0.04f, 0.04f, 0.04f, 0.98f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.98f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.95f);
    colors[ImGuiCol_Border] = ImVec4(0.25f, 0.25f, 0.25f, 0.50f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    // Frames with subtle gradient feel
    colors[ImGuiCol_FrameBg] = ImVec4(0.12f, 0.12f, 0.14f, 0.95f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.18f, 0.18f, 0.20f, 0.95f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.22f, 0.22f, 0.24f, 0.95f);
    // Title bar dark
    colors[ImGuiCol_TitleBg] = ImVec4(0.02f, 0.02f, 0.02f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.08f, 0.10f, 1.00f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    // Scrollbars subtle
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.01f, 0.01f, 0.01f, 0.50f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
    // Neon purple accents
    colors[ImGuiCol_CheckMark] = ImVec4(0.54f, 0.00f, 1.00f, 1.00f);  // #8B00FF neon purple
    colors[ImGuiCol_SliderGrab] = ImVec4(0.54f, 0.00f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.70f, 0.20f, 1.00f, 1.00f);  // Glow variant
    // Buttons with purple hover glow
    colors[ImGuiCol_Button] = ImVec4(0.15f, 0.15f, 0.17f, 0.40f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.54f, 0.00f, 1.00f, 0.30f);  // Purple glow
    colors[ImGuiCol_ButtonActive] = ImVec4(0.54f, 0.00f, 1.00f, 0.60f);
    // Headers/tabs neon
    colors[ImGuiCol_Header] = ImVec4(0.54f, 0.00f, 1.00f, 0.31f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.54f, 0.00f, 1.00f, 0.80f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.70f, 0.20f, 1.00f, 1.00f);
    colors[ImGuiCol_Tab] = ImVec4(0.12f, 0.12f, 0.14f, 0.60f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.54f, 0.00f, 1.00f, 0.50f);  // Purple hover
    colors[ImGuiCol_TabActive] = ImVec4(0.54f, 0.00f, 1.00f, 0.85f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.10f, 0.10f, 0.12f, 0.97f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.20f, 0.20f, 0.22f, 1.00f);
    // Separators purple
    colors[ImGuiCol_Separator] = ImVec4(0.54f, 0.00f, 1.00f, 0.50f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.54f, 0.00f, 1.00f, 0.78f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.54f, 0.00f, 1.00f, 1.00f);
    // Text light
    colors[ImGuiCol_Text] = ImVec4(0.95f, 0.95f, 0.98f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.55f, 1.00f);
    // Other
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.54f, 0.00f, 1.00f, 0.25f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.54f, 0.00f, 1.00f, 0.67f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.70f, 0.20f, 1.00f, 0.95f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.54f, 0.00f, 1.00f, 1.00f);
}