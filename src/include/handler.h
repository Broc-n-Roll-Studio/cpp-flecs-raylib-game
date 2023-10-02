#pragma once

#include "flecs.h"
#include <functional>

namespace broc::handler {
    struct Context {
        std::function<void(flecs::world&)> setup_components;
        std::function<void(flecs::world&)> setup_globals;
        std::function<void(flecs::world&)> setup_systems;
        static void process_contexts(flecs::world& world, std::vector<Context>& contexts);
    };

    template <typename T> class ContextHandler {
      public:
        static Context make_context() {
            return {
                T::setup_components,
                T::setup_globals,
                T::setup_systems,
            };
        }
        static void setup_components(flecs::world& world) {}
        static void setup_globals(flecs::world& world) {}
        static void setup_systems(flecs::world& world) {}
    };
}  // namespace broc::handler
