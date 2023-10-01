#pragma once

#include "flecs.h"

namespace broc {
  namespace camera {
    void setup_components(flecs::world& world);
    void setup_globals(flecs::world& world);
    void setup_systems(flecs::world& world);
  };  // namespace camera
};    // namespace broc
