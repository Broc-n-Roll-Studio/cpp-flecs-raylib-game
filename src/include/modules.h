#pragma once

#include "definitions/input.h"
#include "definitions/physics.h"
#include "definitions/pipelines.h"
#include "definitions/types.h"
#include "flecs.h"
#include "raylib.h"
#include "raymath.h"
#include <iostream>

namespace broc::modules
{
  using namespace broc::types;

  class GamePipelineModule
  {
   public:
    GamePipelineModule(flecs::world &world) {
      world.module<GamePipelineModule>("GamePipelineModule");

      m_render_pipeline = world.component<pipelines::RenderPipeline>();
      m_physics_pipeline = world.component<pipelines::PhysicsPipeline>();

      world.set<pipelines::PhysicsPipeline>(pipelines::PhysicsPipeline().Setup(world));
      world.set<pipelines::RenderPipeline>(pipelines::RenderPipeline().Setup(world));
    }

    flecs::entity m_render_pipeline;
    flecs::entity m_physics_pipeline;
  };

  class CameraModule
  {
   public:
    CameraModule(flecs::world &world) {
      world.module<CameraModule>("CameraModule");

      m_camera3d = world.component<Camera3D>();

      {
        auto cam = Camera3D{
          .position = {0, 10.f, 20.f},
          .target = {0, 2.f, 0},
          .up = {0, 1.f, 0},
          .fovy = 60,
          .projection = CAMERA_PERSPECTIVE,
        };
        world.set<Camera3D>(cam);
      }

      m_follow_player = world.system<TestBody>("Camera Following Player").with<Player>().each([&world](TestBody &t) {
        Camera3D *cam = world.get_mut<Camera3D>();
        const auto cam_sensitivity = 0.05f;
        const auto mouse_delta = GetMouseDelta();

        UpdateCameraPro(cam, Vector3Zero(),
          {
            mouse_delta.x * cam_sensitivity, // Rotation: yaw
            mouse_delta.y * cam_sensitivity, // Rotation: pitch
            0                                // Rotation: roll
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

      m_player_movement =
        world.system<Movable, const Player>("Player Movement Input").each([](Movable &m, const Player &p) {
          m.velocity = Vector3Normalize(input::RetrieveMovementVector());
        });
    }
    flecs::entity m_player_movement;
  };

  class EntityModule
  {
   public:
    EntityModule(flecs::world &world) {
      world.module<EntityModule>("EntityModule");
      m_movable = world.component<Movable>();
      m_drawable = world.component<Drawable>();

      auto render_pipeline = world.get<pipelines::RenderPipeline>();
      auto physics_pipeline = world.get<pipelines::PhysicsPipeline>();

      m_move = world.system<Movable>("Move Entities").each([](Movable &m) {
        m.position.x += m.velocity.x * m.speed_force * GetFrameTime();
        m.position.y += m.velocity.y * m.speed_force * GetFrameTime();
        m.position.z += m.velocity.z * m.speed_force * GetFrameTime();
      });

      m_draw = world.system<TestBody>("Draw Entities").kind(render_pipeline->OnDraw).each([](TestBody &b) {
        auto body_position =
          broc::physics::PhysicsWorld::getInstance()->physics_system->GetBodyInterface().GetCenterOfMassPosition(b.bid);

        std::cout << "X: " << body_position.GetX() << " Y: " << body_position.GetY() << " Z: " << body_position.GetZ()
                  << std::endl;

        DrawCube({body_position.GetX(), body_position.GetY(), body_position.GetZ()}, 5, 5, 5, RED);
      });
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
