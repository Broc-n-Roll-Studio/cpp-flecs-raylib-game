#include "game.h"
#include "context/context.h"
#include <vector>

namespace broc::config {
    void InitializeWorld(flecs::world& world) {
        using namespace context;

        std::vector<context::Context> contexts{
            pipeline::Handler::MakeContext(), input::Handler::MakeContext(),
            entity::Handler::MakeContext(),   player::Handler::MakeContext(),
            enemy::Handler::MakeContext(),    camera::Handler::MakeContext()};

        Context::ProcessContexts(world, contexts);
    }

    void InitializeWindow() {
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window title");
        SetTargetFPS(60);
    }
}  // namespace broc::config
