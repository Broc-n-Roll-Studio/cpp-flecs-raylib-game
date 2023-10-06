cmake_minimum_required(VERSION 3.16)
project(gamez C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")


# Setting parameters for raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games

add_subdirectory(libs/raylib)
add_subdirectory(libs/flecs)
add_subdirectory(libs)

file(GLOB_RECURSE HEADERS src/*.h)
file(GLOB_RECURSE SRC src/*.cpp)

add_executable(${PROJECT_NAME} ${HEADERS} ${SRC})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/include)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib flecs::flecs_static Jolt)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/") # Set the asset path macro to the absolute path on the dev machine
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="relative-path-to-assets-in-the-game-package") # Set the asset path macro in release mode
endif()
