#include "flecs.h"
#include "game.h"
#include "raylib.h"

int main() {
  flecs::world world;

  broc::config::initialize_world(world);
  broc::config::initialize_window();
  while (!WindowShouldClose()) {
    world.progress(GetFrameTime());
  }

  CloseWindow();
  return 0;
}
