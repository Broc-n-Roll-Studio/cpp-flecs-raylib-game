#include "context/context.h"
#include "raymath.h"

namespace broc::context::input {
    using namespace broc::types;

    Vector2 mapper::RetrieveMovementVector() {
        auto left_key = IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A);
        auto right_key = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D);
        auto up_key = IsKeyDown(KEY_UP) || IsKeyDown(KEY_W);
        auto down_key = IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S);
        return {
            static_cast<float>(right_key - left_key),
            static_cast<float>(down_key - up_key),
        };
    }

    void Handler::SetupComponents(flecs::world& world) {}

    void Handler::SetupGlobals(flecs::world& world) {}

    void Handler::SetupSystems(flecs::world& world) {
        auto render_pipeline = world.get<pipeline::RenderPipeline>();

        world.system<Movable, const Player>("Player Movement")
            .each([](Movable& m, const Player& p) {
                m.velocity = Vector2Normalize(mapper::RetrieveMovementVector());
            });

        world.system("Camera Zoom").kind(render_pipeline->OnDraw).iter([](flecs::iter& it) {
            Camera2D* cam = it.world().get_mut<Camera2D>();

            float wheel = GetMouseWheelMove();

            const float minimum_zoom = 0.125f;
            const float maximum_zoom = 5.0f;

            if (wheel != 0)
                cam->zoom = Clamp(cam->zoom + wheel * minimum_zoom, minimum_zoom, maximum_zoom);
        });
    }
}  // namespace broc::context::input
