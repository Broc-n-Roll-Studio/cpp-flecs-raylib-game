#include "player.h"
#include "entity/entity.h"
#include "types.h"

namespace broc::player {
    using namespace types;

    void Handler::setup_components(flecs::world& world) { world.component<Player>(); }

    void Handler::setup_globals(flecs::world& world) {}

    void Handler::setup_systems(flecs::world& world) {
        auto e = world.entity().add<Player>().set([](Movable& m, Drawable& d) {
            m = {{800.0 / 2, 450.0 / 2}, {0, 0}, 300};
            d = {50, RED};
        });
    }
}  // namespace broc::player
