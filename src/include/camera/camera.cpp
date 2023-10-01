#include "camera.h"
#include "flecs.h"
#include "player/player.h"
#include "raylib.h"
#include "types.h"

using namespace broc::types;

void broc::camera::Handler::setup_components(flecs::world& world) { world.component<Camera2D>(); }
void broc::camera::Handler::setup_globals(flecs::world& world) {
  world.set<Camera2D>({{0, 0}, {0, 0}, 0, 1.0f});
}
void broc::camera::Handler::setup_systems(flecs::world& world) {
  world.system<Movable>().with<Player>().each([&world](Movable& m) {
    Camera2D* cam = world.get_mut<Camera2D>();
    cam->target = {m.position.x - GetScreenWidth() * 0.5f / cam->zoom,
                   m.position.y - GetScreenHeight() * 0.5f / cam->zoom};
  });
}
