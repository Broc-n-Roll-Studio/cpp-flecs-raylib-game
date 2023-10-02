#pragma once

#include "flecs.h"
#include "handler.h"

namespace broc {
  namespace pipeline {
    class Handler : public ContextHandler<Handler> {
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
      flecs::entity OnPreDraw;
      flecs::entity OnPostDraw;
    };
  }  // namespace pipeline
}  // namespace broc
