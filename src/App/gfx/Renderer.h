#pragma once

#include "../util.h"

#include <SDL2/SDL_render.h>

#include "Window.h"

class Renderer {
public:
  SDL_Renderer *handle;

  Renderer(Window &window);
  ~Renderer();

  void setVSync(bool enabled);

  void clear();
  void present();
  void setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
  void drawRect(int x, int y, int w, int h);
  void fillRect(int x, int y, int w, int h);
  void drawLine(int x1, int y1, int x2, int y2);
  void drawPoint(int x, int y);
  void drawCircle(int x, int y, int r);
  void fillCircle(int x, int y, int r);
  void drawTexture(SDL_Texture *texture, int x, int y);
};