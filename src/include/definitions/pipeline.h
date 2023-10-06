#pragma once

#include "flecs.h"

namespace broc::pipelines
{
  class RenderPipeline
  {
   public:
    flecs::entity OnDraw;

    RenderPipeline Setup(flecs::world &world);

   private:
    flecs::entity m_OnPreDraw;
    flecs::entity m_OnPostDraw;
  };
} // namespace broc::pipelines
