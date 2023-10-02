#pragma once
#include "flecs.h"
#include "handler.h"

namespace broc::player {
    class Handler : public handler::ContextHandler<Handler> {
      public:
        static void SetupComponents(flecs::world& world);
        static void SetupGlobals(flecs::world& world);
        static void SetupSystems(flecs::world& world);
    };
}  // namespace broc::player
