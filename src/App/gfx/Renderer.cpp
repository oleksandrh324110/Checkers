#include "Renderer.h"

Renderer::Renderer(Window &window) {
  handle = SDL_CreateRenderer(window.handle, -1, SDL_RENDERER_ACCELERATED);
}

Renderer::~Renderer() {
  SDL_DestroyRenderer(handle);
}
