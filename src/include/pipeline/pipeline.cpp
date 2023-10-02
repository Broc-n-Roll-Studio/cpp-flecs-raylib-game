#include "pipeline.h"
#include "raylib.h"

namespace broc::pipeline {
    void Handler::setup_components(flecs::world& world) {
        world.component<pipeline::RenderPipeline>();
    }

    void Handler::setup_globals(flecs::world& world) {
        world.set<pipeline::RenderPipeline>(pipeline::RenderPipeline().setup(world));
    }

    void Handler::setup_systems(flecs::world& world) {}

    RenderPipeline RenderPipeline::setup(flecs::world& world) {
        this->m_OnPreDraw = world.entity().add(flecs::Phase).depends_on(flecs::OnUpdate);
        this->OnDraw = world.entity().add(flecs::Phase).depends_on(this->m_OnPreDraw);
        this->m_OnPostDraw = world.entity().add(flecs::Phase).depends_on(this->OnDraw);

        world.system().kind(this->m_OnPreDraw).iter([](flecs::iter& it) {
            BeginDrawing();
            BeginMode2D(*it.world().get<Camera2D>());
            ClearBackground(RAYWHITE);
        });
        world.system().kind(this->m_OnPostDraw).iter([](flecs::iter& it) {
            DrawFPS(10, 10);
            EndMode2D();
            EndDrawing();
        });

        return *this;
    }
}  // namespace broc::pipeline
