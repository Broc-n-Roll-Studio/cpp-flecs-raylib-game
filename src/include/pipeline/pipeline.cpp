#include "pipeline.h"
#include "raylib.h"

void broc::pipeline::Handler::setup_components(flecs::world& world) {
  world.component<pipeline::RenderPipeline>();
}
void broc::pipeline::Handler::setup_globals(flecs::world& world) {
  world.set<pipeline::RenderPipeline>(pipeline::RenderPipeline().setup(world));
}
void broc::pipeline::Handler::setup_systems(flecs::world& world) {}

broc::pipeline::RenderPipeline broc::pipeline::RenderPipeline::setup(flecs::world& world) {
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

  return *this;
}
