#include "handler.h"

void Context::process_contexts(flecs::world &world, std::vector<Context> &contexts) {
  for (auto context : contexts) {
    context.setup_components(world);
  }
  for (auto context : contexts) {
    context.setup_globals(world);
  }
  for (auto context : contexts) {
    context.setup_systems(world);
  }
}
