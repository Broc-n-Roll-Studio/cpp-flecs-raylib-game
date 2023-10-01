#pragma once

#include "flecs.h"
#include "handler.h"

namespace broc {
  namespace camera {
    class Handler : public ContextHandler<Handler> {
    public:
      static void setup_components(flecs::world& world);
      static void setup_globals(flecs::world& world);
      static void setup_systems(flecs::world& world);
    };
  };  // namespace camera
};    // namespace broc
