#include "raylib.h"
#include "render_pipeline.h"

void broc::pipeline::RenderPipeline::setup(flecs::world& world) {
  this->OnPreDraw = world.entity().add(flecs::Phase).depends_on(flecs::OnUpdate);
  this->OnDraw = world.entity().add(flecs::Phase).depends_on(this->OnPreDraw);
  this->OnPostDraw = world.entity().add(flecs::Phase).depends_on(this->OnDraw);

  world.system().kind(this->OnPreDraw).iter([](flecs::iter& it) {
    BeginDrawing();
    BeginMode2D(*it.world().get<Camera2D>());
    ClearBackground(RAYWHITE);
  });
  world.system().kind(this->OnPostDraw).iter([](flecs::iter& it) {
    DrawFPS(10, 10);
    EndMode2D();
    EndDrawing();
  });
}
