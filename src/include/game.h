#pragma once

#include "flecs.h"

namespace broc {
  namespace config {
    constexpr auto SCREEN_WIDTH = 800;
    constexpr auto SCREEN_HEIGHT = 450;

    void initialize_components(flecs::world& world);
    void initialize_globals(flecs::world& world);
    void initialize_systems(flecs::world& world);
    void initialize_window();
  }  // namespace config
}  // namespace broc
