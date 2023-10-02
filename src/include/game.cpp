#include "game.h"
#include "camera/camera.h"
#include "entity/entity.h"
#include "handler.h"
#include "input/input.h"
#include "pipeline/pipeline.h"
#include "player/player.h"
#include <vector>

namespace broc::config {
    void InitializeWorld(flecs::world& world) {
        std::vector<handler::Context> contexts{
            pipeline::Handler::MakeContext(), input::Handler::MakeContext(),
            entity::Handler::MakeContext(), player::Handler::MakeContext(),
            camera::Handler::MakeContext()};

        handler::Context::ProcessContexts(world, contexts);
    }

    void InitializeWindow() {
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window title");
        SetTargetFPS(60);
    }
}  // namespace broc::config
