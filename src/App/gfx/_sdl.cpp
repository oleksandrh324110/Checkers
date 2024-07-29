#include "_sdl.h"

_SDL::_SDL() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
    throw std::runtime_error("Unable to initialize SDL");
}

_SDL::~_SDL() {
  SDL_Quit();
}
