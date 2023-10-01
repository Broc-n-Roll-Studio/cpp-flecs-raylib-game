#pragma once

#include "flecs.h"
#include "raylib.h"

namespace broc {
  namespace entity {
    struct Movable {
      Vector2 position;
      Vector2 velocity;
      float speed_force;
    };

    struct Drawable {
      float size;
      Color color;
    };

    void setup_components(flecs::world& world);
    void setup_systems(flecs::world& world);
  }  // namespace entity
}  // namespace broc
