#pragma once

#include <Jolt/Jolt.h>
///

#include "Jolt/Physics/Body/BodyID.h"
#include "Jolt/Physics/Collision/Shape/Shape.h"
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
    JPH::Vec3 box_collider_proportions;
  };

  struct StaticBody
  {
    JPH::BodyID bid;
    JPH::Vec3 box_collider_proportions;
  };

  struct Player
  {
  };

  struct Enemy
  {
  };
} // namespace broc::types
