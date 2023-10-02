#pragma once

#include "flecs.h"
#include "handler.h"

namespace broc::pipeline {
    class Handler : public handler::ContextHandler<Handler> {
      public:
        static void setup_components(flecs::world& world);
        static void setup_globals(flecs::world& world);
        static void setup_systems(flecs::world& world);
    };

    class RenderPipeline {
      public:
        flecs::entity OnDraw;

        RenderPipeline setup(flecs::world& world);

      private:
        flecs::entity m_OnPreDraw;
        flecs::entity m_OnPostDraw;
    };
}  // namespace broc::pipeline
