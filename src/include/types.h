#pragma once

#include "raylib.h"

namespace broc::types {
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
}  // namespace broc::types
