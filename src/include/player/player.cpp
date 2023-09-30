#include "entity/entity.h"
#include "player.h"

using broc::entity::Drawable;
using broc::entity::Movable;
using broc::player::Player;

void broc::player::setup(flecs::world& world) {
  world.component<Player>();
  auto e = world.entity().add<Player>().set([](Movable& m, Drawable& d) {
    m = {{800.0 / 2, 450.0 / 2, 0}, {1, 0, 0}, 1};
    d = {50, RED};
  });
}
