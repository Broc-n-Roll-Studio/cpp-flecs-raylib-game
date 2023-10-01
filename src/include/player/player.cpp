#include "entity/entity.h"
#include "player.h"

using broc::entity::Drawable;
using broc::entity::Movable;
using broc::player::Player;

void broc::player::setup_components(flecs::world& world) { world.component<Player>(); }

void broc::player::setup_systems(flecs::world& world) {
  auto e = world.entity().add<Player>().set([](Movable& m, Drawable& d) {
    m = {{800.0 / 2, 450.0 / 2}, {0, 0}, 300};
    d = {50, RED};
  });
}
