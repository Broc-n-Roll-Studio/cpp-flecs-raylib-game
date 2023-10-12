#pragma once

#include "flecs.h"

namespace broc::config
{
  constexpr auto SCREEN_WIDTH = 800;
  constexpr auto SCREEN_HEIGHT = 450;
  constexpr auto WINDOW_TITLE = "BrocNRoll";

  void InitializeWindow();
} // namespace broc::config

namespace broc::world
{
  class TickWorld
  {
   public:
    TickWorld(const TickWorld &obj) = delete;

    ~TickWorld() {
      delete instancePtr;
    }

    static TickWorld *getInstance() {
      if (instancePtr == nullptr) {
        instancePtr = new TickWorld();
      }

      return instancePtr;
    }

    flecs::world value;

   private:
    TickWorld() {}

    static TickWorld *instancePtr;
  };
  void InitializeTickWorld();
} // namespace broc::world
