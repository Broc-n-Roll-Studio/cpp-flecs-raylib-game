#include "input.h"
#include "flecs.h"
#include "raymath.h"
#include "types.h"

namespace broc::input {
    using namespace broc::types;

    Vector2 mapper::retrieve_movement_vector() {
        auto left_key = IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A);
        auto right_key = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D);
        auto up_key = IsKeyDown(KEY_UP) || IsKeyDown(KEY_W);
        auto down_key = IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S);
        return {
            static_cast<float>(right_key - left_key),
            static_cast<float>(down_key - up_key),
        };
    }

    void Handler::setup_components(flecs::world& world) {}

    void Handler::setup_globals(flecs::world& world) {}

    void Handler::setup_systems(flecs::world& world) {
        world.system<Movable, const Player>().each([](Movable& m, const Player& p) {
            m.velocity = Vector2Normalize(mapper::retrieve_movement_vector());
        });
    }
}  // namespace broc::input
