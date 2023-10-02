#include "game.h"
#include "camera/camera.h"
#include "entity/entity.h"
#include "handler.h"
#include "input/input.h"
#include "pipeline/pipeline.h"
#include "player/player.h"
#include <vector>

namespace broc::config {
    void initialize_world(flecs::world& world) {
        std::vector<handler::Context> contexts{
            pipeline::Handler::make_context(), input::Handler::make_context(),
            entity::Handler::make_context(), player::Handler::make_context(),
            camera::Handler::make_context()};

        handler::Context::process_contexts(world, contexts);
    }

    void initialize_window() {
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window title");
        SetTargetFPS(60);
    }
}  // namespace broc::config
