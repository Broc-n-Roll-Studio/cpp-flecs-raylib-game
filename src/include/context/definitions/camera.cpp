#include "context/context.h"
#include "raymath.h"

namespace broc::context::camera {
    using namespace broc::types;

    void Handler::SetupComponents(flecs::world& world) {
        world.component<Camera2D>();
    }

    void Handler::SetupGlobals(flecs::world& world) {
        world.set<Camera2D>({{0, 0}, {0, 0}, 0, 1.0f});
    }

    void Handler::SetupSystems(flecs::world& world) {
        world.system<Movable>("Camera Following Player").with<Player>().each([&world](Movable& m) {
            Camera2D* cam = world.get_mut<Camera2D>();

            cam->target = {m.position.x - GetScreenWidth() * 0.5f / cam->zoom,
                           m.position.y - GetScreenHeight() * 0.5f / cam->zoom};
        });
    }
}  // namespace broc::context::camera
