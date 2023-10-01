#include "entity/entity.h"
#include "flecs.h"
#include "input.h"
#include "player/player.h"
#include "raylib.h"
#include "raymath.h"

using broc::entity::Movable;
using broc::player::Player;

Vector2 broc::input::handler::retrieve_movement_vector() {
  auto left_key = IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A);
  auto right_key = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D);
  auto up_key = IsKeyDown(KEY_UP) || IsKeyDown(KEY_W);
  auto down_key = IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S);
  return {
      (float)(right_key - left_key),
      (float)(down_key - up_key),
  };
}

void broc::input::setup_systems(flecs::world& world) {
  world.system<Movable, const Player>().each([](Movable& m, const Player& p) {
    m.velocity = Vector2Normalize(broc::input::handler::retrieve_movement_vector());
  });
}
