#pragma once

#include <Jolt/Jolt.h>
///

#include "Jolt/Physics/Body/BodyID.h"
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

  struct TestBody
  {
    JPH::BodyID bid;
    JPH::Vec3 boxColliderProportions;
    Vector3 boxDrawProportions;
    Color boxColor;
  };
  struct TestBodyStatic
  {
    JPH::BodyID bid;
    JPH::Vec3 boxColliderProportions;
    Vector3 boxDrawProportions;
    Color boxColor;
  };

  struct Player
  {
  };

  struct Enemy
  {
  };
} // namespace broc::types
