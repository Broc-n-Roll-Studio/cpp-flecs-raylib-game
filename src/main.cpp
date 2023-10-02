#include "flecs.h"
#include "game.h"
#include "raylib.h"

int main() {
    flecs::world world;

    broc::config::InitializeWorld(world);
    broc::config::InitializeWindow();

    while (!WindowShouldClose()) {
        world.progress(GetFrameTime());
    }

    CloseWindow();
    return 0;
}
