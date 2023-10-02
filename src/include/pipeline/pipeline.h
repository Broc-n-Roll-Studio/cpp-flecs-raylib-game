#pragma once

#include "flecs.h"
#include "handler.h"

namespace broc::pipeline {
    class Handler : public handler::ContextHandler<Handler> {
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
}  // namespace broc::pipeline
