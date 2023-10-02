#pragma once

#include "flecs.h"
#include "handler.h"
#include "raylib.h"

namespace broc::input {
    class Handler : public handler::ContextHandler<Handler> {
      public:
        static void SetupComponents(flecs::world& world);
        static void SetupGlobals(flecs::world& world);
        static void SetupSystems(flecs::world& world);
    };

    namespace mapper {
        Vector2 RetrieveMovementVector();
    }

}  // namespace broc::input
