#pragma once

#include "definitions/input.h"
#include "definitions/pipeline.h"
#include "definitions/types.h"
#include "flecs.h"
#include "raylib.h"
#include "raymath.h"

namespace broc::modules
{
  using namespace broc::types;

  class GamePipelineModule
  {
   public:
    GamePipelineModule(flecs::world &world) {
      world.module<GamePipelineModule>("GamePipelineModule");

      m_render_pipeline = world.component<pipelines::RenderPipeline>();

      world.set<pipelines::RenderPipeline>(pipelines::RenderPipeline().Setup(world));
    }

    flecs::entity m_render_pipeline;
  };

  class CameraModule
  {
   public:
    CameraModule(flecs::world &world) {
      world.module<CameraModule>("CameraModule");

      m_camera3d = world.component<Camera3D>();

      {
        auto cam = Camera3D{
          .position = {0, 2, 4},
          .target = {0, 2, 0},
          .up = {0, 1, 0},
          .fovy = 60,
          .projection = CAMERA_PERSPECTIVE,
        };
        world.set<Camera3D>(cam);
      }

      m_follow_player = world.system<Movable>("Camera Following Player").with<Player>().each([&world](Movable &m) {
        Camera3D *cam = world.get_mut<Camera3D>();
        cam->position = Vector3Add(m.position, {0, 16, 25});
        cam->target = Vector3Add(m.position, {0, 10, 0});

        UpdateCameraPro(cam, {0, 0, 0},
          {
            GetMouseDelta().x * 0.05f, // Rotation: yaw
            GetMouseDelta().y * 0.05f, // Rotation: pitch
            0.0f                       // Rotation: roll
          },
          GetMouseWheelMove() * 2.0f);
      });
    }

    flecs::entity m_camera3d;
    flecs::entity m_follow_player;
  };

  class InputModule
  {
   public:
    InputModule(flecs::world &world) {
      world.module<InputModule>("InputModule");
      auto render_pipeline = world.get<pipelines::RenderPipeline>();

      m_player_movement =
        world.system<Movable, const Player>("Player Movement Input").each([](Movable &m, const Player &p) {
          m.velocity = Vector3Normalize(input::RetrieveMovementVector());
        });

      m_camera_zoom = world.system("Camera Zoom Input").kind(render_pipeline->OnDraw).iter([](flecs::iter &it) {
        Camera2D *cam = it.world().get_mut<Camera2D>();

        float wheel = GetMouseWheelMove();

        const float minimum_zoom = 0.125f;
        const float maximum_zoom = 5.0f;

        if (wheel != 0) {
          cam->zoom = Clamp(cam->zoom + wheel * minimum_zoom, minimum_zoom, maximum_zoom);
        }
      });
    }
    flecs::entity m_player_movement;
    flecs::entity m_camera_zoom;
  };

  class EntityModule
  {
   public:
    EntityModule(flecs::world &world) {
      world.module<EntityModule>("EntityModule");
      m_movable = world.component<Movable>();
      m_drawable = world.component<Drawable>();

      auto render_pipeline = world.get<pipelines::RenderPipeline>();

      m_move = world.system<Movable>("Move Entities").each([](Movable &m) {
        m.position.x += m.velocity.x * m.speed_force * GetFrameTime();
        m.position.y += m.velocity.y * m.speed_force * GetFrameTime();
        m.position.z += m.velocity.z * m.speed_force * GetFrameTime();
      });

      m_draw = world.system<Drawable, Movable>("Draw Entities")
                 .kind(render_pipeline->OnDraw)
                 .each([](Drawable &d, Movable &m) { DrawCube(m.position, d.size, d.size, d.size, d.color); });
    }

    flecs::entity m_movable;
    flecs::entity m_drawable;
    flecs::entity m_move;
    flecs::entity m_draw;
  };

  class PlayerModule
  {
   public:
    PlayerModule(flecs::world &world) {
      world.module<PlayerModule>("PlayerModule");
      m_player = world.component<Player>();
    }

    flecs::entity m_player;
  };

  class EnemyModule
  {
   public:
    EnemyModule(flecs::world &world) {
      world.module<EnemyModule>("EnemyModule");

      m_enemy = world.component<Enemy>();

      // m_chase_player =
      //   world.system<Movable>("Enemy Chasing Player").with<Enemy>().iter([](flecs::iter &it, Movable *m) {
      //     auto player = it.world().filter_builder<Movable>().with<Player>().build().first().get<Movable>();
      //     Vector2 aux;
      //
      //     for (auto i : it) {
      //       aux.x = player->position.x - m[i].position.x;
      //       aux.y = player->position.y - m[i].position.y;
      //
      //       const float nullify_speed_threshold = m[i].speed_force * 0.0083333;
      //
      //       if (fabs(aux.x) < nullify_speed_threshold && fabs(aux.y) < nullify_speed_threshold) {
      //         m[i].velocity = Vector2Zero();
      //       } else {
      //         m[i].velocity = Vector2Normalize(aux);
      //       }
      //     }
      //   });
    }

    flecs::entity m_enemy;
    // flecs::entity m_chase_player;
  };
} // namespace broc::modules
