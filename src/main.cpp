#include "camera/camera.h"
#include "entity/entity.h"
#include "flecs.h"
#include "input/input.h"
#include "pipeline/pipeline.h"
#include "pipeline/render_pipeline.h"
#include "player/player.h"
#include "raylib.h"

constexpr auto SCREEN_WIDTH = 800;
constexpr auto SCREEN_HEIGHT = 450;

int main() {
  flecs::world world;

  broc::entity::setup_components(world);
  broc::player::setup_components(world);
  broc::camera::setup_components(world);
  broc::camera::setup_globals(world);

  broc::pipeline::RenderPipeline render_pipeline;
  render_pipeline.setup(world);
  world.set<broc::pipeline::RenderPipeline>(render_pipeline);

  broc::input::setup_systems(world);
  broc::entity::setup_systems(world);
  broc::player::setup_systems(world);
  broc::camera::setup_systems(world);

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window title");
  SetTargetFPS(60);

  auto main_cam = world.get<Camera2D>();

  while (!WindowShouldClose()) {
    world.progress(GetFrameTime());
  }

  CloseWindow();
  return 0;
}
