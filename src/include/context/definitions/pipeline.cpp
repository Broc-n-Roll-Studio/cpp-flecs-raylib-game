#include "context/context.h"
#include "raymath.h"

namespace broc::context::pipeline {
    void Handler::SetupComponents(flecs::world& world) {
        world.component<pipeline::RenderPipeline>();
    }

    void Handler::SetupGlobals(flecs::world& world) {
        world.set<pipeline::RenderPipeline>(pipeline::RenderPipeline().Setup(world));
    }

    void Handler::SetupSystems(flecs::world& world) {}

    RenderPipeline RenderPipeline::Setup(flecs::world& world) {
        this->m_OnPreDraw = world.entity().add(flecs::Phase).depends_on(flecs::OnUpdate);
        this->OnDraw = world.entity().add(flecs::Phase).depends_on(this->m_OnPreDraw);
        this->m_OnPostDraw = world.entity().add(flecs::Phase).depends_on(this->OnDraw);

        world.system("Pre Draw").kind(this->m_OnPreDraw).iter([](flecs::iter& it) {
            auto camera = it.world().get_mut<Camera2D>();

            BeginDrawing();
            BeginMode2D(*camera);
            ClearBackground(RAYWHITE);
        });
        world.system("Post Draw").kind(this->m_OnPostDraw).iter([](flecs::iter& it) {
            EndMode2D();
            DrawFPS(10, 10);
            EndDrawing();
        });

        return *this;
    }
}  // namespace broc::context::pipeline
