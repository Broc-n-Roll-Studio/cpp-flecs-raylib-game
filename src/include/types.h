#pragma once

#include "raylib.h"

namespace broc {
  namespace types {
    struct Movable {
      Vector2 position;
      Vector2 velocity;
      float speed_force;
    };

    struct Drawable {
      float size;
      Color color;
    };

    struct Player {};
  }  // namespace types
}  // namespace broc
