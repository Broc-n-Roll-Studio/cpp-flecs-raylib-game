#pragma once

#include "raylib.h"

namespace broc::types
{
  struct Movable
  {
    Vector3 position;
    Vector3 velocity;
    float speed_force;
  };

  struct Drawable
  {
    float size;
    Color color;
  };

  struct Player
  {
  };

  struct Enemy
  {
  };
} // namespace broc::types
