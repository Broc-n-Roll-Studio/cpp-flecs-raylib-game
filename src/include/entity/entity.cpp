#include "entity.h"
#include "pipeline/pipeline.h"
#include "raylib.h"

void broc::entity::setup_components(flecs::world& world) {
  world.component<Movable>();
  world.component<Drawable>();
}

void broc::entity::setup_systems(flecs::world& world) {
  world.system<Movable>().kind<broc::pipeline::Logic>().each([](Movable& m) {
    m.position.x += m.velocity.x * m.speed_force * GetFrameTime();
    m.position.y += m.velocity.y * m.speed_force * GetFrameTime();
  });

  world.system<Drawable, Movable>().kind<broc::pipeline::Draw>().each([](Drawable& d, Movable& m) {
    DrawCube({m.position.x, m.position.y, 0}, d.size, d.size, 0, d.color);
  });
}
