// offsets.h
#pragma once
#include <cstdint>

struct Vector3 { float x, y, z; };

namespace offsets {
    constexpr std::uintptr_t dwLocalPlayerPawn = 0x1E3D470;
    constexpr std::uintptr_t dwEntityList      = 0x1D15F88;

    constexpr std::uintptr_t m_iHealth     = 0x334;
    constexpr std::uintptr_t m_vecOrigin  = 0x127C;
    constexpr std::uintptr_t m_iTeamNum   = 0x3CB;
}
