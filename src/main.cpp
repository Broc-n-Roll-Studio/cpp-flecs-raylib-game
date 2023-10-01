#include "flecs.h"
#include "game.h"
#include "raylib.h"

int main() {
  flecs::world world;

  broc::config::initialize_components(world);
  broc::config::initialize_globals(world);
  broc::config::initialize_systems(world);
  broc::config::initialize_window();

  while (!WindowShouldClose()) {
    world.progress(GetFrameTime());
  }

  CloseWindow();
  return 0;
}
