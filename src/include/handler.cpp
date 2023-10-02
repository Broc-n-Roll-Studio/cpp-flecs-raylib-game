#include "handler.h"

namespace broc::handler {
    void Context::ProcessContexts(flecs::world &world, std::vector<Context> &contexts) {
        for (auto context : contexts) {
            context.SetupComponents(world);
        }
        for (auto context : contexts) {
            context.SetupGlobals(world);
        }
        for (auto context : contexts) {
            context.SetupSystems(world);
        }
    }
}  // namespace broc::handler
