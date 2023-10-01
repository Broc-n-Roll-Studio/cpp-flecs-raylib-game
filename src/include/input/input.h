#pragma once

#include "flecs.h"
#include "raylib.h"

namespace broc {
  namespace input {
    namespace handler {
      Vector2 retrieve_movement_vector();
    }
    void setup_systems(flecs::world& world);
  }  // namespace input
}  // namespace broc
