#include "game.h"
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

    world.entity().add<types::Player>().set([](types::TestBody &b) {
      b = {.bid = {}, .boxColliderProportions = {5, 5, 5}, .boxDrawProportions = {5, 5, 5}, .boxColor = RED};
    });

    // world.entity("Enemy Entity").add<types::Enemy>().set([](types::Movable &m, types::Drawable &d) {
    //   m = {.position = {50, 6, 50}, .velocity = {0, 0}, .speed_force = 200};
    //   d = {.size = 32.0, .color = BLUE};
    // });
  }

  void InitializeWindow() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window title");
    SetTargetFPS(60);
  }
} // namespace broc::config
