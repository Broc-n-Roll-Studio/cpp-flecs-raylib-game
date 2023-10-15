#include "pipelines.h"
#include "definitions/physics.h"
#include "definitions/types.h"
#include "raylib.h"
#include "raymath.h"

broc::pipelines::RenderPipeline broc::pipelines::RenderPipeline::Setup(flecs::world &world) {
  this->m_OnPreDraw = world.entity().add(flecs::Phase).depends_on(flecs::PostUpdate);
  this->OnDraw = world.entity().add(flecs::Phase).depends_on(this->m_OnPreDraw);
  this->m_OnPostDraw = world.entity().add(flecs::Phase).depends_on(this->OnDraw);

  world.system("Pre Draw").kind(this->m_OnPreDraw).iter([](flecs::iter &it) {
    BeginDrawing();
    BeginMode3D(*it.world().get<Camera3D>());
    ClearBackground(DARKGRAY);
  });
  world.system("Post Draw").kind(this->m_OnPostDraw).iter([](flecs::iter &it) {
    EndMode3D();
    EndDrawing();
  });

  return *this;
}

broc::world::PhysicsWorld *broc::world::PhysicsWorld::instancePtr = nullptr;
broc::pipelines::PhysicsPipeline broc::pipelines::PhysicsPipeline::Setup(flecs::world &world) {
  this->OnFixedUpdate = world.entity().add(flecs::Phase).depends_on(flecs::OnUpdate);
  this->m_OnPostFixedUpdate = world.entity().add(flecs::Phase).depends_on(this->OnFixedUpdate);

  world.system("Post Fixed Update").kind(this->m_OnPostFixedUpdate).iter([](flecs::iter &it) {
    broc::world::PhysicsWorld::getInstance()->Update(GetFrameTime());
  });

  return *this;
}
