#include "input.h"

Vector3 broc::input::RetrieveMovementVector() {
  auto left_key = IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A);
  auto right_key = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D);
  auto up_key = IsKeyDown(KEY_UP) || IsKeyDown(KEY_W);
  auto down_key = IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S);
  return {static_cast<float>(right_key - left_key), 0, static_cast<float>(down_key - up_key)};
}
