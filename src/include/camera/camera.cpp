#include "camera.h"
#include "entity/entity.h"
#include "flecs.h"
#include "player/player.h"
#include "raylib.h"

using broc::entity::Movable;
using broc::player::Player;

void broc::camera::setup_components(flecs::world& world) { world.component<Camera2D>(); }
void broc::camera::setup_globals(flecs::world& world) {
  world.set<Camera2D>({{0, 0}, {0, 0}, 0, 1.0f});
}
void broc::camera::setup_systems(flecs::world& world) {
  world.system<Movable>().with<Player>().each([&world](Movable& m) {
    Camera2D* cam = world.get_mut<Camera2D>();
    cam->target = {m.position.x - GetScreenWidth() * 0.5f / cam->zoom,
                   m.position.y - GetScreenHeight() * 0.5f / cam->zoom};
  });
}
