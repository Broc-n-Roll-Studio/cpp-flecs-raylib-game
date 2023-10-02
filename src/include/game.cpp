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
            broc::pipeline::Handler::make_context(), broc::input::Handler::make_context(),
            broc::entity::Handler::make_context(), broc::player::Handler::make_context(),
            broc::camera::Handler::make_context()};

        handler::Context::process_contexts(world, contexts);
    }

    void initialize_window() {
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window title");
        SetTargetFPS(60);
    }
}  // namespace broc::config
