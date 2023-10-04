#include "pipeline.h"
#include "raylib.h"

namespace broc::pipelines {
    RenderPipeline RenderPipeline::Setup(flecs::world& world) {
        this->m_OnPreDraw = world.entity().add(flecs::Phase).depends_on(flecs::OnUpdate);
        this->OnDraw = world.entity().add(flecs::Phase).depends_on(this->m_OnPreDraw);
        this->m_OnPostDraw = world.entity().add(flecs::Phase).depends_on(this->OnDraw);

        world.system("Pre Draw").kind(this->m_OnPreDraw).iter([](flecs::iter& it) {
            BeginDrawing();
            BeginMode2D(*it.world().get<Camera2D>());
            ClearBackground(BLACK);
        });
        world.system("Post Draw").kind(this->m_OnPostDraw).iter([](flecs::iter& it) {
            DrawFPS(10, 10);
            EndMode2D();
            EndDrawing();
        });

        return *this;
    }
}  // namespace broc::pipelines
