#include "game.h"
#include "definitions/physics.h"
#include "definitions/types.h"
#include "modules.h"

#include "Jolt/Math/Vec3.h"
#include "Jolt/Physics/Body/BodyCreationSettings.h"
#include "Jolt/Physics/Collision/Shape/BoxShape.h"

void broc::config::InitializeWindow() {
  InitWindow(broc::config::SCREEN_WIDTH, broc::config::SCREEN_HEIGHT, broc::config::WINDOW_TITLE);
  SetTargetFPS(60);
}

broc::world::TickWorld *broc::world::TickWorld::instancePtr = nullptr;
void broc::world::InitializeTickWorld() {
  auto tick_world = broc::world::TickWorld::getInstance();

  tick_world->value.import <modules::GamePipelineModule>();
  tick_world->value.import <modules::InputModule>();
  tick_world->value.import <modules::EntityModule>();
  tick_world->value.import <modules::EnemyModule>();
  tick_world->value.import <modules::PlayerModule>();
  tick_world->value.import <modules::CameraModule>();

  broc::world::PhysicsWorld::getInstance();

  // Player
  auto player_body = physics::CreateBodyWrapper(new JPH::BoxShape({5, 5, 5}), {0, 10, 0}, JPH::Quat::sIdentity(),
    JPH::EMotionType::Dynamic, physics::Layers::MOVING, JPH::EActivation::Activate);

  tick_world->value.entity().add<types::Player>().set([&](types::DynamicBody &b, types::Drawable &d) {
    b = {.bid = player_body};
    d = {.proportions = {5, 5, 5}, .color = RED};
  });

  // Ground
  auto ground_body = physics::CreateBodyWrapper(new JPH::BoxShape({128, 1, 128}), {0, -1, 0});

  tick_world->value.entity().set([&](types::StaticBody &b, types::Drawable &d) {
    b = {.bid = ground_body};
    d = {.proportions = {128, 1, 128}, .color = LIME};
  });

  broc::world::PhysicsWorld::getInstance()->physics_system->OptimizeBroadPhase();
}
