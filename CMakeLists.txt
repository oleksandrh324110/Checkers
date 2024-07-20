cmake_minimum_required(VERSION 3.5)

project(sdl_learn)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory("lib/SDL")
add_subdirectory("lib/glm")

file(GLOB IMGUI_SOURCES
  "lib/imgui/*.cpp"
  "lib/imgui/backends/imgui_impl_sdl2.cpp"
  "lib/imgui/backends/imgui_impl_sdlrenderer2.cpp"
)
add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC "lib/imgui" "lib/SDL/include")
include_directories("lib/imgui" "lib/imgui/backends")

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(main "${SOURCES}")
target_link_libraries(main SDL2-static SDL2main imgui glm)
