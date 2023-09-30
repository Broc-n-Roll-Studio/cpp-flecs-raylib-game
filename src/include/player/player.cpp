#include "entity/entity.h"
#include "player.h"

void broc::player::setup(flecs::world& world) {
  auto e = world.entity().set([](broc::entity::Movable& m, broc::entity::Drawable& d) {
    m = {{800.0 / 2, 450.0 / 2, 0}, {1, 0, 0}, 1};
    d = {50, RED};
  });
}
