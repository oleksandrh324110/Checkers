#include "Window.h"

Window::Window(const char *title, int x, int y, int w, int h, Uint32 flags) {
  handle = SDL_CreateWindow(title, x, y, w, h, flags);
  if (handle == nullptr)
    throw std::runtime_error("Unable to create window");
}

Window::~Window() {
  SDL_DestroyWindow(handle);
}
