#include "entity.h"
#include "pipeline/pipeline.h"

void broc::entity::setup(flecs::world& world) {
  world.component<Movable>();

  world.system<Movable>().kind<broc::pipeline::Logic>().each([](Movable& m) {
    m.position.x += m.velocity.x * m.speed_force;
    m.position.y += m.velocity.y * m.speed_force;
  });

  world.system<Drawable, Movable>().kind<broc::pipeline::Draw>().each(
      [](Drawable& d, Movable& m) { DrawCube(m.position, d.size, d.size, 0, d.color); });
}
