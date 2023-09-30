#pragma once

#include "flecs.h"
#include "raylib.h"

namespace broc {
  namespace entity {
    struct Movable {
      Vector3 position;
      Vector3 velocity;
      float speed_force;
    };

    struct Drawable {
      float size;
      Color color;
    };

    void setup(flecs::world& world);
  }  // namespace entity
}  // namespace broc
