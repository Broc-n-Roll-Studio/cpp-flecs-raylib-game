#include "entity.h"
#include "pipeline/pipeline.h"
#include "types.h"

using namespace broc::types;

void broc::entity::Handler::setup_components(flecs::world& world) {
  world.component<Movable>();
  world.component<Drawable>();
}
void broc::entity::Handler::setup_globals(flecs::world& world) {}
void broc::entity::Handler::setup_systems(flecs::world& world) {
  auto render_pipeline = world.get<broc::pipeline::RenderPipeline>();

  world.system<Movable>().each([](Movable& m) {
    m.position.x += m.velocity.x * m.speed_force * GetFrameTime();
    m.position.y += m.velocity.y * m.speed_force * GetFrameTime();
  });

  world.system<Drawable, Movable>().kind(render_pipeline->OnDraw).each([](Drawable& d, Movable& m) {
    DrawCube({m.position.x, m.position.y, 0}, d.size, d.size, 0, d.color);
  });
}
