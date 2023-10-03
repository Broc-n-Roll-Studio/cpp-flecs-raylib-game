#include "context/context.h"
#include "raymath.h"

namespace broc::context::enemy {
    using namespace types;

    void Handler::SetupComponents(flecs::world& world) {
        world.component<Enemy>();
    }

    void Handler::SetupGlobals(flecs::world& world) {}

    void Handler::SetupSystems(flecs::world& world) {
        auto e = world.entity().add<Enemy>().set([](Movable& m, Drawable& d) {
            m = {.position = {50, 50}, .velocity = {0, 0}, .speed_force = 100};
            d = {.size = {32.0}, .color = BLUE};
        });

        world.system<Movable>().with<Enemy>().iter([](flecs::iter& it, Movable* m) {
            auto player = it.world()
                              .filter_builder<Movable>()
                              .with<Player>()
                              .build()
                              .first()
                              .get<Movable>();
            Vector2 aux;
            for (auto i : it) {
                aux.x = player->position.x - m[i].position.x;
                aux.y = player->position.y - m[i].position.y;

                m[i].velocity = Vector2Normalize(aux);
            }
        });
    }
}  // namespace broc::context::enemy
