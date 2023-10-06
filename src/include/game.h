#pragma once

#include "flecs.h"

namespace broc::config
{
  constexpr auto SCREEN_WIDTH = 800;
  constexpr auto SCREEN_HEIGHT = 450;

  void InitializeWorld(flecs::world &world);
  void InitializeWindow();
} // namespace broc::config
