#include "physics.h"

bool broc::physics::ObjectLayerPairFilterImpl::ShouldCollide(
  JPH::ObjectLayer inObject1, JPH::ObjectLayer inObject2) const {
  switch (inObject1) {
  case Layers::NON_MOVING:
    return inObject2 == Layers::MOVING; // Non moving only collides with moving
  case Layers::MOVING:
    return true; // Moving collides with everything
  default:
    JPH_ASSERT(false);
    return false;
  }
}

uint broc::physics::BPLayerInterfaceImpl::GetNumBroadPhaseLayers() const {
  return BroadPhaseLayers::NUM_LAYERS;
}

JPH::BroadPhaseLayer broc::physics::BPLayerInterfaceImpl::GetBroadPhaseLayer(JPH::ObjectLayer inLayer) const {
  JPH_ASSERT(inLayer < Layers::NUM_LAYERS);
  return mObjectToBroadPhase[inLayer];
}

#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
const char *broc::physics::BPLayerInterfaceImpl::GetBroadPhaseLayerName(JPH::BroadPhaseLayer inLayer) const {
  switch ((JPH::BroadPhaseLayer::Type)inLayer) {
  case (JPH::BroadPhaseLayer::Type)BroadPhaseLayers::NON_MOVING:
    return "NON_MOVING";
  case (JPH::BroadPhaseLayer::Type)BroadPhaseLayers::MOVING:
    return "MOVING";
  default:
    JPH_ASSERT(false);
    return "INVALID";
  }
}
#endif

bool broc::physics::ObjectVsBroadPhaseLayerFilterImpl::ShouldCollide(
  JPH::ObjectLayer inLayer1, JPH::BroadPhaseLayer inLayer2) const {
  switch (inLayer1) {
  case Layers::NON_MOVING:
    return inLayer2 == BroadPhaseLayers::MOVING;
  case Layers::MOVING:
    return true;
  default:
    JPH_ASSERT(false);
    return false;
  }
}

JPH::ValidateResult broc::physics::MyContactListener::OnContactValidate(const JPH::Body &inBody1,
  const JPH::Body &inBody2, JPH::RVec3Arg inBaseOffset, const JPH::CollideShapeResult &inCollisionResult) {
  std::cout << "Contact validate callback" << std::endl;

  // Allows you to ignore a contact before it is created (using layers to not make objects collide is cheaper!)
  return JPH::ValidateResult::AcceptAllContactsForThisBodyPair;
}

void broc::physics::MyContactListener::OnContactAdded(const JPH::Body &inBody1, const JPH::Body &inBody2,
  const JPH::ContactManifold &inManifold, JPH::ContactSettings &ioSettings) {
  std::cout << "A contact was added" << std::endl;
}

void broc::physics::MyContactListener::OnContactPersisted(const JPH::Body &inBody1, const JPH::Body &inBody2,
  const JPH::ContactManifold &inManifold, JPH::ContactSettings &ioSettings) {
  std::cout << "A contact was persisted" << std::endl;
}

void broc::physics::MyContactListener::OnContactRemoved(const JPH::SubShapeIDPair &inSubShapePair) {
  std::cout << "A contact was removed" << std::endl;
}

void broc::physics::MyBodyActivationListener::OnBodyActivated(const JPH::BodyID &inBodyID, JPH::uint64 inBodyUserData) {
  std::cout << "A body got activated" << std::endl;
}

void broc::physics::MyBodyActivationListener::OnBodyDeactivated(
  const JPH::BodyID &inBodyID, JPH::uint64 inBodyUserData) {
  std::cout << "A body went to sleep" << std::endl;
}

JPH::BodyID broc::physics::CreateBodyWrapper(JPH::Shape *shape, JPH::Vec3 initialPos, JPH::Quat rotation,
  JPH::EMotionType motionType, JPH::ObjectLayer layer, JPH::EActivation eActivation) {

  auto body_settings = JPH::BodyCreationSettings(shape, initialPos, rotation, motionType, layer);

  return broc::world::PhysicsWorld::getInstance()->physics_system->GetBodyInterface().CreateAndAddBody(
    body_settings, eActivation);
}
