#pragma once

#include "flecs.h"
#include "raylib.h"
#include <functional>

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

    struct Enemy {};
}  // namespace broc::types

namespace broc::context {
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

    namespace pipeline {
        class Handler : public ContextHandler<Handler> {
          public:
            static void SetupComponents(flecs::world& world);
            static void SetupGlobals(flecs::world& world);
            static void SetupSystems(flecs::world& world);
        };

        class RenderPipeline {
          public:
            flecs::entity OnDraw;

            RenderPipeline Setup(flecs::world& world);

          private:
            flecs::entity m_OnPreDraw;
            flecs::entity m_OnPostDraw;
        };
    }  // namespace pipeline

    namespace camera {
        class Handler : public ContextHandler<Handler> {
          public:
            static void SetupComponents(flecs::world& world);
            static void SetupGlobals(flecs::world& world);
            static void SetupSystems(flecs::world& world);
        };
    }  // namespace camera

    namespace input {
        class Handler : public ContextHandler<Handler> {
          public:
            static void SetupComponents(flecs::world& world);
            static void SetupGlobals(flecs::world& world);
            static void SetupSystems(flecs::world& world);
        };

        namespace mapper {
            Vector2 RetrieveMovementVector();
        }

    }  // namespace input

    namespace entity {
        class Handler : public ContextHandler<Handler> {
          public:
            static void SetupComponents(flecs::world& world);
            static void SetupGlobals(flecs::world& world);
            static void SetupSystems(flecs::world& world);
        };

    }  // namespace entity

    namespace player {
        class Handler : public ContextHandler<Handler> {
          public:
            static void SetupComponents(flecs::world& world);
            static void SetupGlobals(flecs::world& world);
            static void SetupSystems(flecs::world& world);
        };
    }  // namespace player

    namespace enemy {
        class Handler : public ContextHandler<Handler> {
          public:
            static void SetupComponents(flecs::world& world);
            static void SetupGlobals(flecs::world& world);
            static void SetupSystems(flecs::world& world);
        };
    }  // namespace enemy
}  // namespace broc::context
