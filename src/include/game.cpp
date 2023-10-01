#include "camera/camera.h"
#include "entity/entity.h"
#include "game.h"
#include "input/input.h"
#include "pipeline/render_pipeline.h"
#include "player/player.h"

void broc::config::initialize_components(flecs::world& world) {
  broc::entity::setup_components(world);
  broc::player::setup_components(world);
  broc::camera::setup_components(world);
  broc::pipeline::RenderPipeline render_pipeline;
  render_pipeline.setup(world);
  world.set<broc::pipeline::RenderPipeline>(render_pipeline);
}

void broc::config::initialize_globals(flecs::world& world) { broc::camera::setup_globals(world); }

void broc::config::initialize_systems(flecs::world& world) {
  broc::input::setup_systems(world);
  broc::entity::setup_systems(world);
  broc::player::setup_systems(world);
  broc::camera::setup_systems(world);
}

void broc::config::initialize_window() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window title");
  SetTargetFPS(60);
}
