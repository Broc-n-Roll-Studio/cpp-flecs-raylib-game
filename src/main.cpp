#include "entity/entity.h"
#include "flecs.h"
#include "pipeline/pipeline.h"
#include "raylib.h"

constexpr auto SCREEN_WIDTH = 800;
constexpr auto SCREEN_HEIGHT = 450;

int main() {
  flecs::world world;

  flecs::pipeline logic_pipeline
      = world.pipeline().with(flecs::System).with<broc::pipeline::Logic>().build();
  flecs::pipeline draw_pipeline
      = world.pipeline().with(flecs::System).with<broc::pipeline::Draw>().build();

  auto e = world.entity().set([](broc::entity::Movable& m, broc::entity::Drawable& d) {
    m = {{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0}, {1, 0, 0}, 1};
    d = {50, RED};
  });

  broc::entity::setup(world);

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window title");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    world.set_pipeline(logic_pipeline);
    world.progress(GetFrameTime());

    BeginDrawing();
    ClearBackground(RAYWHITE);

    world.set_pipeline(draw_pipeline);
    world.progress(GetFrameTime());

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
