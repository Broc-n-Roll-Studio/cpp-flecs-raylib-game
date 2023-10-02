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
        world.system<Movable, const Player>().each([](Movable& m, const Player& p) {
            m.velocity = Vector2Normalize(mapper::RetrieveMovementVector());
        });
    }
}  // namespace broc::context::input
