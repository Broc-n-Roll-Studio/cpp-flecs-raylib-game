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

      m_follow_player =
        world.system<DynamicBody>("Camera Following Player").with<Player>().each([&world](DynamicBody &t) {
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

      m_player_movement = world.system<DynamicBody>("Player Movement Input").with<Player>().each([](DynamicBody &b) {
        // m.velocity = Vector3Normalize(input::RetrieveMovementVector());
      });
    }
    flecs::entity m_player_movement;
  };

  class EntityModule
  {
   public:
    EntityModule(flecs::world &world) {
      world.module<EntityModule>("EntityModule");
      m_dynamic_body = world.component<DynamicBody>();
      m_static_body = world.component<StaticBody>();
      m_drawable = world.component<Drawable>();

      auto render_pipeline = world.get<pipelines::RenderPipeline>();
      auto physics_pipeline = world.get<pipelines::PhysicsPipeline>();

      m_draw_dynamic =
        world.system<const DynamicBody, const Drawable>("Draw Entities")
          .kind(render_pipeline->OnDraw)
          .each([](const DynamicBody &b, const Drawable &d) {
            auto body_position =
              broc::physics::PhysicsWorld::getInstance()->physics_system->GetBodyInterface().GetCenterOfMassPosition(
                b.bid);

            DrawCubeV({body_position.GetX(), body_position.GetY(), body_position.GetZ()}, d.proportions, d.color);
          });

      m_draw_static =
        world.system<const StaticBody, const Drawable>("Draw Entities Static")
          .kind(render_pipeline->OnDraw)
          .each([](const StaticBody &b, const Drawable &d) {
            auto body_position =
              broc::physics::PhysicsWorld::getInstance()->physics_system->GetBodyInterface().GetCenterOfMassPosition(
                b.bid);

            DrawCubeV({body_position.GetX(), body_position.GetY(), body_position.GetZ()}, d.proportions, d.color);
          });
    }

    flecs::entity m_drawable;
    flecs::entity m_dynamic_body;
    flecs::entity m_static_body;

    // flecs::entity m_move;
    flecs::entity m_draw_dynamic;
    flecs::entity m_draw_static;
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
    }

    flecs::entity m_enemy;
    // flecs::entity m_chase_player;
  };
} // namespace broc::modules
