#include "input.h"
#include "flecs.h"
#include "raymath.h"
#include "types.h"

using namespace broc::types;

Vector2 broc::input::mapper::retrieve_movement_vector() {
  auto left_key = IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A);
  auto right_key = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D);
  auto up_key = IsKeyDown(KEY_UP) || IsKeyDown(KEY_W);
  auto down_key = IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S);
  return {
      (float)(right_key - left_key),
      (float)(down_key - up_key),
  };
}

void broc::input::Handler::setup_components(flecs::world& world) {}
void broc::input::Handler::setup_globals(flecs::world& world) {}
void broc::input::Handler::setup_systems(flecs::world& world) {
  world.system<Movable, const Player>().each([](Movable& m, const Player& p) {
    m.velocity = Vector2Normalize(broc::input::mapper::retrieve_movement_vector());
  });
}
