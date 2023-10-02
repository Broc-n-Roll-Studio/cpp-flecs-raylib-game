#include "handler.h"
#include <iostream>

void Context::process_contexts(flecs::world &world, std::vector<Context> &contexts) {
  std::cout << contexts.size() << std::endl;
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
