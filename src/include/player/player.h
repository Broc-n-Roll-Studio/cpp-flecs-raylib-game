#pragma once
#include "flecs.h"

namespace broc {
  namespace player {
    struct Player {};
    void setup_components(flecs::world& world);
    void setup_systems(flecs::world& world);
  }  // namespace player
}  // namespace broc
