#include "flecs.h"
#include "raylib.h"

struct Movable {
  Vector2 position;
  Vector2 velocity;
  float speed_force;
};

constexpr auto SCREEN_WIDTH = 800;
constexpr auto SCREEN_HEIGHT = 450;

int main() {
  flecs::world world;

  world.system<Movable>().each([](Movable& m) {
    m.position.x += m.velocity.x * m.speed_force;
    m.position.y += m.velocity.y * m.speed_force;
  });

  auto e = world.entity().set([](Movable& m) {
    m = {{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, {1, 0}, 1};
  });

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window title");
  SetTargetFPS(60);

  Texture2D texture = LoadTexture(ASSETS_PATH "test.png");

  while (!WindowShouldClose()) {
    world.progress(GetFrameTime());

    auto player_movable = e.get<Movable>();

    BeginDrawing();

    ClearBackground(RAYWHITE);

    const int texture_x = player_movable->position.x - texture.width / 2;
    const int texture_y = player_movable->position.y - texture.height / 2;
    DrawTexture(texture, texture_x, texture_y, WHITE);

    const char* text = "OMG! IT WORKS!";
    const Vector2 text_size = MeasureTextEx(GetFontDefault(), text, 20, 1);
    DrawText(text, SCREEN_WIDTH / 2 - text_size.x / 2,
             texture_y + texture.height + text_size.y + 10, 20, BLACK);

    EndDrawing();
  }

  UnloadTexture(texture);

  CloseWindow();
  return 0;
}
