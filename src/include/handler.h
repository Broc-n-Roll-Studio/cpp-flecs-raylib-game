#pragma once

#include "flecs.h"
#include <functional>

namespace broc::handler {
    struct Context {
        std::function<void(flecs::world&)> SetupComponents;
        std::function<void(flecs::world&)> SetupGlobals;
        std::function<void(flecs::world&)> SetupSystems;
        static void ProcessContexts(flecs::world& world, std::vector<Context>& contexts);
    };

    template <typename T> class ContextHandler {
      public:
        static Context MakeContext() {
            return {
                T::SetupComponents,
                T::SetupGlobals,
                T::SetupSystems,
            };
        }
        static void SetupComponents(flecs::world& world) {}
        static void SetupGlobals(flecs::world& world) {}
        static void SetupSystems(flecs::world& world) {}
    };
}  // namespace broc::handler
