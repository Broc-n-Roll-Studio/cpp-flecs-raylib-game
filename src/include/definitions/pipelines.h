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

  class PhysicsPipeline
  {
   public:
    flecs::entity OnFixedUpdate;

    PhysicsPipeline Setup(flecs::world &world);

   private:
    flecs::entity m_OnPostFixedUpdate;
  };
} // namespace broc::pipelines
