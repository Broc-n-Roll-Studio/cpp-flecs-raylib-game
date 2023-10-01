#pragma once

#include "flecs.h"

namespace broc {
  namespace pipeline {
    class RenderPipeline {
    public:
      flecs::entity OnDraw;

      void setup(flecs::world& world);

    private:
      flecs::entity OnPreDraw;
      flecs::entity OnPostDraw;
    };
  }  // namespace pipeline
}  // namespace broc
