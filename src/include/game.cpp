#include "game.h"
#include "definitions/types.h"
#include "modules.h"

namespace broc::config
{
  void InitializeWorld(flecs::world &world) {
    world.import <modules::GamePipelineModule>();
    world.import <modules::InputModule>();
    world.import <modules::EntityModule>();
    world.import <modules::EnemyModule>();
    world.import <modules::PlayerModule>();
    world.import <modules::CameraModule>();

    // Player
    world.entity().add<types::Player>().set([](types::DynamicBody &b, types::Drawable &d) {
      b = {.bid = {}, .box_collider_proportions = {5, 5, 5}};
      d = {.proportions = {5, 5, 5}, .color = RED};
    });

    // Ground
    world.entity().set([](types::StaticBody &b, types::Drawable &d) {
      b = {.bid = {}, .box_collider_proportions = {128, 1, 128}};
      d = {.proportions = {128, 1, 128}, .color = LIME};
    });
  }

  void InitializeWindow() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window title");
    SetTargetFPS(60);
  }
} // namespace broc::config
