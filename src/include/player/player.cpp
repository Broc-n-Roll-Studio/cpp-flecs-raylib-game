#include "entity/entity.h"
#include "player.h"
#include "types.h"

using namespace broc::types;

void broc::player::Handler::setup_components(flecs::world& world) { world.component<Player>(); }
void broc::player::Handler::setup_globals(flecs::world& world) {}
void broc::player::Handler::setup_systems(flecs::world& world) {
  auto e = world.entity().add<Player>().set([](Movable& m, Drawable& d) {
    m = {{800.0 / 2, 450.0 / 2}, {0, 0}, 300};
    d = {50, RED};
  });
}
