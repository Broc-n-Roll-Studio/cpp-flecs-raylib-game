#include "pipelines.h"
#include <Jolt/Jolt.h>
#include <iostream>
///
#include "Jolt/Physics/Body/BodyCreationSettings.h"
#include "Jolt/Physics/Collision/Shape/BoxShape.h"
#include "Jolt/Physics/Collision/Shape/SphereShape.h"
#include "definitions/physics.h"
#include "definitions/types.h"
#include "raylib.h"
#include "raymath.h"

broc::pipelines::RenderPipeline broc::pipelines::RenderPipeline::Setup(flecs::world &world) {
  this->m_OnPreDraw = world.entity().add(flecs::Phase).depends_on(flecs::PostUpdate);
  this->OnDraw = world.entity().add(flecs::Phase).depends_on(this->m_OnPreDraw);
  this->m_OnPostDraw = world.entity().add(flecs::Phase).depends_on(this->OnDraw);

  world.system("Pre Draw").kind(this->m_OnPreDraw).iter([](flecs::iter &it) {
    auto cam = it.world().get<Camera3D>();

    BeginDrawing();
    BeginMode3D(*cam);
    ClearBackground(DARKGRAY);
    DrawPlane({0, 0, 0}, {128, 128}, LIME);
    DrawCube({5, 5, 5}, 5, 5, 5, YELLOW);
  });
  world.system("Post Draw").kind(this->m_OnPostDraw).iter([](flecs::iter &it) {
    EndMode3D();
    EndDrawing();
  });

  return *this;
}

broc::physics::PhysicsWorld *broc::physics::PhysicsWorld::instancePtr = nullptr;
broc::pipelines::PhysicsPipeline broc::pipelines::PhysicsPipeline::Setup(flecs::world &world) {
  this->OnFixedUpdate = world.entity().add(flecs::Phase).depends_on(flecs::OnUpdate);
  this->m_OnPostFixedUpdate = world.entity().add(flecs::Phase).depends_on(this->OnFixedUpdate);

  world.system<broc::types::TestBody>("Physics Startup")
    .kind(flecs::OnStart)
    .iter([](flecs::iter &it, types::TestBody *b) {
      std::cout << "PHYSICS STARTUP" << std::endl;

      // The main way to interact with the bodies in the physics system is through the body interface. There is a
      // locking and a non-locking variant of this. We're going to use the locking version (even though we're not
      // planning to access bodies from multiple threads)
      JPH::BodyInterface &body_interface =
        broc::physics::PhysicsWorld::getInstance()->physics_system->GetBodyInterface();

      for (auto i : it) {
        // Now create a dynamic body to bounce on the floor
        // Note that this uses the shorthand version of creating and adding a body to the world
        JPH::BodyCreationSettings sphere_settings(new JPH::BoxShape({25, 25, 25}), JPH::Vec3(5.0, 20.0, 5.0),
          JPH::Quat::sIdentity(), JPH::EMotionType::Dynamic, broc::physics::Layers::MOVING);
        b[i].bid = body_interface.CreateAndAddBody(sphere_settings, JPH::EActivation::Activate);

        // Now you can interact with the dynamic body, in this case we're going to give it a velocity.
        // (note that if we had used CreateBody then we could have set the velocity straight on the body before adding
        // it to the physics system)
        body_interface.SetLinearVelocity(b[i].bid, JPH::Vec3(0.0f, 0.0f, 0.0f));
      }

      // Optional step: Before starting the physics simulation you can optimize the broad phase. This improves collision
      // detection performance (it's pointless here because we only have 2 bodies). You should definitely not call this
      // every frame or when e.g. streaming in a new level section as it is an expensive operation. Instead insert all
      // new objects in batches instead of 1 at a time to keep the broad phase efficient.
      broc::physics::PhysicsWorld::getInstance()->physics_system->OptimizeBroadPhase();
    });

  world.system("Post Fixed Update").kind(this->m_OnPostFixedUpdate).iter([](flecs::iter &it) {
    broc::physics::PhysicsWorld::getInstance()->Update(GetFrameTime());
  });

  return *this;
}
