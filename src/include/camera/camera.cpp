#include "camera.h"

#include "entity/entity.h"
#include "flecs.h"
#include "pipeline/pipeline.h"
#include "player/player.h"
#include "raylib.h"

using broc::entity::Movable;
using broc::player::Player;

void broc::camera::setup_systems(flecs::world& world) {
  world.component<Camera2D>();
  world.set<Camera2D>({{0, 0}, {0, 0}, 0, 1.0f});
  world.system<Movable>().with<Player>().kind<pipeline::Logic>().each([&world](Movable& m) {
    Camera2D* cam = world.get_mut<Camera2D>();
    cam->target = {m.position.x - GetScreenWidth() * 0.5f / cam->zoom,
                   m.position.y - GetScreenHeight() * 0.5f / cam->zoom};
  });
}
