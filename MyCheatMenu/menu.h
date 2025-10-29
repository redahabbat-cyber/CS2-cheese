#pragma once
#include "imgui.h"

// RAGNAREK-Style UI Configs (expanded for CS2)
namespace WeaveUI {
    struct Legit {
        bool aimbot = false;
        bool triggerbot = false;
        bool rcs = false;
        float fov = 90.0f;
        int smooth = 5;
        int hitbox = 0;  // 0=Head, 1=Chest, etc.
    };
    struct Rage {
        bool rage = false;
        bool antiaim = false;
        bool fakelag = false;
    };
    struct Visuals {
        bool esp = false;
        bool chams = false;
        bool glow = false;
        ImVec4 box_color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    };
    struct Config {
        bool show_menu = true;
        int active_tab = 0;
    };

    extern Legit legit;
    extern Rage rage;
    extern Visuals visuals;
    extern Config config;

    void RenderMenu();
}

// Themes
namespace Themes {
    void ApplyRagnarokTheme();  // RAGNAREK-v2 neon purple
}