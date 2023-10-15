#pragma once

#include <Jolt/Jolt.h>
///

#include "Jolt/Physics/Body/BodyID.h"
#include "raylib.h"

namespace broc::types
{
  struct Stats
  {
    float movement_speed;
  };

  struct Drawable
  {
    Vector3 proportions;
    Color color;
  };

  struct DynamicBody
  {
    JPH::BodyID bid;
  };

  struct StaticBody
  {
    JPH::BodyID bid;
  };

  struct Player
  {
  };

  struct Enemy
  {
  };
} // namespace broc::types
