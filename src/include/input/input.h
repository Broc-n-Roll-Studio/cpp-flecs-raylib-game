#pragma once

#include "flecs.h"
#include "handler.h"
#include "raylib.h"

namespace broc::input {
    class Handler : public handler::ContextHandler<Handler> {
      public:
        static void setup_components(flecs::world& world);
        static void setup_globals(flecs::world& world);
        static void setup_systems(flecs::world& world);
    };

    namespace mapper {
        Vector2 retrieve_movement_vector();
    }

}  // namespace broc::input
