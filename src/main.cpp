#include "flecs.h"
#include "game.h"
#include "raylib.h"

int main() {
  broc::world::InitializeTickWorld();
  broc::config::InitializeWindow();

  DisableCursor();

  auto world = broc::world::TickWorld::getInstance();
  while (!WindowShouldClose()) {
    world->value.progress(GetFrameTime());
  }

  CloseWindow();
  return 0;
}
