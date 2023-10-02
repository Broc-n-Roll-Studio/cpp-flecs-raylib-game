#include "context/context.h"

namespace broc::context::player {
    using namespace types;

    void Handler::SetupComponents(flecs::world& world) { world.component<Player>(); }

    void Handler::SetupGlobals(flecs::world& world) {}

    void Handler::SetupSystems(flecs::world& world) {
        auto e = world.entity().add<Player>().set([](Movable& m, Drawable& d) {
            m = {{800.0 / 2, 450.0 / 2}, {0, 0}, 300};
            d = {50, RED};
        });
    }
}  // namespace broc::context::player
