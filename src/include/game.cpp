#include "game.h"
#include "camera/camera.h"
#include "entity/entity.h"
#include "handler.h"
#include "input/input.h"
#include "pipeline/render_pipeline.h"
#include "player/player.h"
#include <vector>

void broc::config::initialize_world(flecs::world& world) {
  broc::pipeline::RenderPipeline render_pipeline;
  render_pipeline.setup(world);
  world.set<broc::pipeline::RenderPipeline>(render_pipeline);
  std::vector<Context> contexts{
      broc::input::Handler::make_context(), broc::entity::Handler::make_context(),
      broc::player::Handler::make_context(), broc::camera::Handler::make_context()};
  Context::process_contexts(world, contexts);
}

void broc::config::initialize_window() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window title");
  SetTargetFPS(60);
}
