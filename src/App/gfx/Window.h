#pragma once

#include "../util.h"
#include "_sdl.h"

class Window {
public:
  SDL_Window *handle;
  int width, height;

  Window(const char *title, int x, int y, int w, int h, Uint32 flags);
  ~Window();
};