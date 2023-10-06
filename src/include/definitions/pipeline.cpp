#include "pipeline.h"
#include "raylib.h"

namespace broc::pipelines
{
  RenderPipeline RenderPipeline::Setup(flecs::world &world) {
    this->m_OnPreDraw = world.entity().add(flecs::Phase).depends_on(flecs::OnUpdate);
    this->OnDraw = world.entity().add(flecs::Phase).depends_on(this->m_OnPreDraw);
    this->m_OnPostDraw = world.entity().add(flecs::Phase).depends_on(this->OnDraw);

    world.system("Pre Draw").kind(this->m_OnPreDraw).iter([](flecs::iter &it) {
      BeginDrawing();
      BeginMode3D(*it.world().get<Camera3D>());
      ClearBackground(DARKGRAY);
      DrawPlane({0, 0, 0}, {128, 128}, LIME);
    });
    world.system("Post Draw").kind(this->m_OnPostDraw).iter([](flecs::iter &it) {
      DrawFPS(10, 10);
      EndMode3D();
      EndDrawing();
    });

    return *this;
  }
} // namespace broc::pipelines
