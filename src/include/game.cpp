#include "game.h"
#include "definitions/types.h"
#include "modules.h"

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

  // Player
  tick_world->value.entity().add<types::Player>().set([](types::DynamicBody &b, types::Drawable &d) {
    b = {.bid = {}, .box_collider_proportions = {5, 5, 5}};
    d = {.proportions = {5, 5, 5}, .color = RED};
  });

  // Ground
  tick_world->value.entity().set([](types::StaticBody &b, types::Drawable &d) {
    b = {.bid = {}, .box_collider_proportions = {128, 1, 128}};
    d = {.proportions = {128, 1, 128}, .color = LIME};
  });
}
