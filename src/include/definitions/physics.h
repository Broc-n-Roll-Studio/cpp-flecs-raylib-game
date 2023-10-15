#pragma once

#include <Jolt/Jolt.h>

//
#include "Jolt/Core/Factory.h"
#include "Jolt/Core/JobSystemThreadPool.h"
#include "Jolt/Core/TempAllocator.h"
#include "Jolt/Math/Quat.h"
#include "Jolt/Math/Vec3.h"
#include "Jolt/Physics/Body/BodyActivationListener.h"
#include "Jolt/Physics/Body/BodyCreationSettings.h"
#include "Jolt/Physics/Body/BodyID.h"
#include "Jolt/Physics/Body/BodyInterface.h"
#include "Jolt/Physics/Collision/ObjectLayer.h"
#include "Jolt/Physics/Collision/Shape/Shape.h"
#include "Jolt/Physics/EActivation.h"
#include "Jolt/Physics/PhysicsSettings.h"
#include "Jolt/Physics/PhysicsSystem.h"
#include "Jolt/RegisterTypes.h"

//
#include <cstdarg>
#include <iostream>
#include <memory>
#include <thread>

namespace broc::physics
{
  // Layer that objects can be in, determines which other objects it can collide with
  // Typically you at least want to have 1 layer for moving bodies and 1 layer for static bodies, but you can have more
  // layers if you want. E.g. you could have a layer for high detail collision (which is not used by the physics
  // simulation but only if you do collision testing).
  namespace Layers
  {
    static constexpr JPH::ObjectLayer NON_MOVING = 0;
    static constexpr JPH::ObjectLayer MOVING = 1;
    static constexpr JPH::ObjectLayer NUM_LAYERS = 2;
  }; // namespace Layers

  // Callback for traces, connect this to your own trace function if you have one
  static void TraceImpl(const char *inFMT, ...) {
    // Format the message
    va_list list;
    va_start(list, inFMT);
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), inFMT, list);
    va_end(list);

    // Print to the TTY
    std::cout << buffer << std::endl;
  }

#ifdef JPH_ENABLE_ASSERTS
  static bool AssertFailedImpl(const char *inExpression, const char *inMessage, const char *inFile, uint inLine) {
    // Print to the TTY
    std::cout << inFile << ":" << inLine << ": (" << inExpression << ") " << (inMessage != nullptr ? inMessage : "")
              << std::endl;

    // Breakpoint
    return true;
  };
#endif

  /// Class that determines if two object layers can collide
  class ObjectLayerPairFilterImpl : public JPH::ObjectLayerPairFilter
  {
   public:
    virtual bool ShouldCollide(JPH::ObjectLayer inObject1, JPH::ObjectLayer inObject2) const override;
  };

  // Each broadphase layer results in a separate bounding volume tree in the broad phase. You at least want to have
  // a layer for non-moving and moving objects to avoid having to update a tree full of static objects every frame.
  // You can have a 1-on-1 mapping between object layers and broadphase layers (like in this case) but if you have
  // many object layers you'll be creating many broad phase trees, which is not efficient. If you want to fine tune
  // your broadphase layers define JPH_TRACK_BROADPHASE_STATS and look at the stats reported on the TTY.
  namespace BroadPhaseLayers
  {
    static constexpr JPH::BroadPhaseLayer NON_MOVING(0);
    static constexpr JPH::BroadPhaseLayer MOVING(1);
    static constexpr uint NUM_LAYERS(2);
  }; // namespace BroadPhaseLayers

  // BroadPhaseLayerInterface implementation
  // This defines a mapping between object and broadphase layers.
  class BPLayerInterfaceImpl final : public JPH::BroadPhaseLayerInterface
  {
   public:
    BPLayerInterfaceImpl() {
      // Create a mapping table from object to broad phase layer
      mObjectToBroadPhase[Layers::NON_MOVING] = BroadPhaseLayers::NON_MOVING;
      mObjectToBroadPhase[Layers::MOVING] = BroadPhaseLayers::MOVING;
    }
    virtual uint GetNumBroadPhaseLayers() const override;
    virtual JPH::BroadPhaseLayer GetBroadPhaseLayer(JPH::ObjectLayer inLayer) const override;

#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
    virtual const char *GetBroadPhaseLayerName(JPH::BroadPhaseLayer inLayer) const override;
#endif

   private:
    JPH::BroadPhaseLayer mObjectToBroadPhase[Layers::NUM_LAYERS];
  };

  /// Class that determines if an object layer can collide with a broadphase layer
  class ObjectVsBroadPhaseLayerFilterImpl : public JPH::ObjectVsBroadPhaseLayerFilter
  {
   public:
    virtual bool ShouldCollide(JPH::ObjectLayer inLayer1, JPH::BroadPhaseLayer inLayer2) const override;
  };

  // An example contact listener
  class MyContactListener : public JPH::ContactListener
  {
   public:
    // See: ContactListener
    virtual JPH::ValidateResult OnContactValidate(const JPH::Body &inBody1, const JPH::Body &inBody2,
      JPH::RVec3Arg inBaseOffset, const JPH::CollideShapeResult &inCollisionResult) override;

    virtual void OnContactAdded(const JPH::Body &inBody1, const JPH::Body &inBody2,
      const JPH::ContactManifold &inManifold, JPH::ContactSettings &ioSettings) override;

    virtual void OnContactPersisted(const JPH::Body &inBody1, const JPH::Body &inBody2,
      const JPH::ContactManifold &inManifold, JPH::ContactSettings &ioSettings) override;

    virtual void OnContactRemoved(const JPH::SubShapeIDPair &inSubShapePair) override;
  };

  // An example activation listener
  class MyBodyActivationListener : public JPH::BodyActivationListener
  {
   public:
    virtual void OnBodyActivated(const JPH::BodyID &inBodyID, JPH::uint64 inBodyUserData) override;

    virtual void OnBodyDeactivated(const JPH::BodyID &inBodyID, JPH::uint64 inBodyUserData) override;
  };

  class PhysicsWorld
  {
   public:
    PhysicsWorld(const PhysicsWorld &obj) = delete;

    static PhysicsWorld *getInstance() {
      if (instancePtr == nullptr) {
        instancePtr = new PhysicsWorld();
      }

      return instancePtr;
    }

    ~PhysicsWorld() {
      // Unregisters all types with the factory and cleans up the default material
      JPH::UnregisterTypes();

      // Destroy the factory
      delete JPH::Factory::sInstance;
      JPH::Factory::sInstance = nullptr;
      delete instancePtr;
    }

    void Update(float deltaTime) {
      // If you take larger steps than 1 / 60th of a second you need to do multiple collision steps in order to keep the
      // simulation stable. Do 1 collision step per 1 / 60th of a second (round up).
      const int cCollisionSteps = 1;

      // Step the world
      this->physics_system->Update(deltaTime, cCollisionSteps, this->temp_allocator.get(), this->job_system.get());
    }

    std::unique_ptr<JPH::TempAllocatorImpl> temp_allocator;
    std::unique_ptr<JPH::JobSystemThreadPool> job_system;

    std::unique_ptr<JPH::PhysicsSystem> physics_system;

    std::unique_ptr<MyBodyActivationListener> body_activation_listener;
    std::unique_ptr<MyContactListener> contact_listener;

    std::unique_ptr<BPLayerInterfaceImpl> broad_phase_layer_interface;
    std::unique_ptr<ObjectVsBroadPhaseLayerFilterImpl> object_vs_broadphase_layer_filter;
    std::unique_ptr<ObjectLayerPairFilterImpl> object_vs_object_layer_filter;

   private:
    static PhysicsWorld *instancePtr;

    PhysicsWorld() {
      // Register allocation hook
      JPH::RegisterDefaultAllocator();

      // Install callbacks
      JPH::Trace = TraceImpl;
      JPH_IF_ENABLE_ASSERTS(JPH::AssertFailed = AssertFailedImpl;)

      // Create a factory
      JPH::Factory::sInstance = new JPH::Factory();

      // Register all Jolt physics types
      JPH::RegisterTypes();

      // We need a temp allocator for temporary allocations during the physics update. We're
      // pre-allocating 10 MB to avoid having to do allocations during the physics update.
      // B.t.w. 10 MB is way too much for this example but it is a typical value you can use.
      // If you don't want to pre-allocate you can also use TempAllocatorMalloc to fall back to
      // malloc / free.
      this->temp_allocator = std::make_unique<JPH::TempAllocatorImpl>(10 * 1024 * 1024);

      // We need a job system that will execute physics jobs on multiple threads. Typically
      // you would implement the JobSystem interface yourself and let Jolt Physics run on top
      // of your own job scheduler. JobSystemThreadPool is an example implementation.
      this->job_system = std::make_unique<JPH::JobSystemThreadPool>(
        JPH::cMaxPhysicsJobs, JPH::cMaxPhysicsBarriers, JPH::thread::hardware_concurrency() - 1);

      // Create mapping table from object layer to broadphase layer
      // Note: As this is an interface, PhysicsSystem will take a reference to this so this instance needs to stay
      // alive!
      this->broad_phase_layer_interface = std::make_unique<BPLayerInterfaceImpl>();

      // Create class that filters object vs broadphase layers
      // Note: As this is an interface, PhysicsSystem will take a reference to this so this instance needs to stay
      // alive!
      this->object_vs_broadphase_layer_filter = std::make_unique<ObjectVsBroadPhaseLayerFilterImpl>();

      // Create class that filters object vs object layers
      // Note: As this is an interface, PhysicsSystem will take a reference to this so this instance needs to stay
      // alive!
      this->object_vs_object_layer_filter = std::make_unique<ObjectLayerPairFilterImpl>();

      // This is the max amount of rigid bodies that you can add to the physics system. If you try to add more you'll
      // get an error. Note: This value is low because this is a simple test. For a real project use something in the
      // order of 65536.
      const uint cMaxBodies = 1024;

      // This determines how many mutexes to allocate to protect rigid bodies from concurrent access. Set it to 0 for
      // the default settings.
      const uint cNumBodyMutexes = 0;

      // This is the max amount of body pairs that can be queued at any time (the broad phase will detect overlapping
      // body pairs based on their bounding boxes and will insert them into a queue for the narrowphase). If you make
      // this buffer too small the queue will fill up and the broad phase jobs will start to do narrow phase work. This
      // is slightly less efficient. Note: This value is low because this is a simple test. For a real project use
      // something in the order of 65536.
      const uint cMaxBodyPairs = 1024;

      // This is the maximum size of the contact constraint buffer. If more contacts (collisions between bodies) are
      // detected than this number then these contacts will be ignored and bodies will start interpenetrating / fall
      // through the world. Note: This value is low because this is a simple test. For a real project use something in
      // the order of 10240.
      const uint cMaxContactConstraints = 1024;

      // Now we can create the actual physics system.
      this->physics_system = std::make_unique<JPH::PhysicsSystem>();
      physics_system->Init(cMaxBodies, cNumBodyMutexes, cMaxBodyPairs, cMaxContactConstraints,
        *this->broad_phase_layer_interface, *this->object_vs_broadphase_layer_filter,
        *this->object_vs_object_layer_filter);

      // A body activation listener gets notified when bodies activate and go to sleep
      // Note that this is called from a job so whatever you do here needs to be thread safe.
      // Registering one is entirely optional.
      this->body_activation_listener = std::make_unique<MyBodyActivationListener>();
      this->physics_system->SetBodyActivationListener(body_activation_listener.get());

      // A contact listener gets notified when bodies (are about to) collide, and when they separate again.
      // Note that this is called from a job so whatever you do here needs to be thread safe.
      // Registering one is entirely optional.
      this->contact_listener = std::make_unique<MyContactListener>();
      this->physics_system->SetContactListener(contact_listener.get());
    }
  };

  JPH::BodyID CreateBodyWrapper(JPH::Shape *shape, JPH::Vec3 initialPos = {0, 0, 0},
    JPH::Quat rotation = JPH::Quat::sIdentity(), JPH::EMotionType motionType = JPH::EMotionType::Static,
    JPH::ObjectLayer layer = physics::Layers::NON_MOVING,
    JPH::EActivation eActivation = JPH::EActivation::DontActivate);

} // namespace broc::physics
