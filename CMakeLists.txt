cmake_minimum_required(VERSION 3.5)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

set(CMAKE_BUILD_TYPE Debug)

project(Checkers)

add_subdirectory("lib/SDL")
add_subdirectory("lib/cglm")

file(GLOB IMGUI_SOURCES
  "lib/imgui/*.cpp"
  "lib/imgui/backends/imgui_impl_sdl2.cpp"
  "lib/imgui/backends/imgui_impl_sdlrenderer2.cpp"
)
add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC "lib/imgui" "lib/SDL/include")
include_directories("lib/imgui" "lib/imgui/backends")

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.c")
add_executable(main "${SOURCES}")
target_link_libraries(main SDL2-static imgui cglm)
