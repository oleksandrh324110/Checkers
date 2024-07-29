#include "util.h"

#include "gfx/Renderer.h"
#include "gfx/Window.h"
#include "gfx/_imgui.h"
#include "gfx/_sdl.h"

class Checkers {
  _SDL sdl;
  Window window = Window("Checkers", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 720, SDL_WINDOW_RESIZABLE);
  Renderer renderer = Renderer(window);
  _ImGui imgui;

  Checkers();
  ~Checkers();
};