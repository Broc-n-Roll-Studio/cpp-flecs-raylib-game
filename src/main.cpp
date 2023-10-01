#include "camera/camera.h"
#include "entity/entity.h"
#include "flecs.h"
#include "input/input.h"
#include "pipeline/pipeline.h"
#include "player/player.h"
#include "raylib.h"

constexpr auto SCREEN_WIDTH = 800;
constexpr auto SCREEN_HEIGHT = 450;

int main() {
  flecs::world world;

  flecs::pipeline logic_pipeline
      = world.pipeline().with(flecs::System).with<broc::pipeline::Logic>().build();
  flecs::pipeline draw_pipeline
      = world.pipeline().with(flecs::System).with<broc::pipeline::Draw>().build();

  broc::entity::setup_components(world);
  broc::player::setup_components(world);

  broc::input::setup_systems(world);
  broc::entity::setup_systems(world);
  broc::player::setup_systems(world);
  broc::camera::setup_systems(world);

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window title");
  SetTargetFPS(60);

  auto main_cam = world.get<Camera2D>();

  while (!WindowShouldClose()) {
    world.set_pipeline(logic_pipeline);
    world.progress(GetFrameTime());

    BeginDrawing();
    BeginMode2D(*main_cam);
    ClearBackground(RAYWHITE);

    world.set_pipeline(draw_pipeline);
    world.progress(GetFrameTime());

    EndMode2D();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
