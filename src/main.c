#include "SDL_rect.h"
#include <stdbool.h>

#include <SDL2/SDL.h>

#define WIDTH 720
#define HEIGHT 720

#define CELL_SIZE WIDTH / 8

typedef enum { WHITE, BLACK } Turn;
typedef enum { MAN, KING } Piece;

typedef struct {
  struct {
    int x, y;
  } pos;
} Mouse;

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;

  bool is_running;

  Turn turn;
  Piece board[8][8];
} State;

State state;

void init();
void destroy();
void update();
void render();
void main_loop();

int main(void) {
  init();
  main_loop();
  destroy();
}

void init() {
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
  state.window = SDL_CreateWindow("Checkers", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, 720, 720, 0);
  state.renderer = SDL_CreateRenderer(state.window, -1, 0);
  state.is_running = true;
}

void destroy() {
  SDL_DestroyRenderer(state.renderer);
  SDL_DestroyWindow(state.window);
  SDL_Quit();
}

void update() {}

void render() {
  SDL_SetRenderDrawColor(state.renderer, 50, 50, 50, 255);
  SDL_RenderClear(state.renderer);

  SDL_SetRenderDrawColor(state.renderer, 255, 150, 0, 255);
  for (size_t i = 0; i < 8; i++) {
    for (size_t j = i % 2; j < 8; j += 2) {
      SDL_Rect cell = {CELL_SIZE * j, CELL_SIZE * i, CELL_SIZE, CELL_SIZE};
      SDL_RenderFillRect(state.renderer, &cell);
    }
  }

  SDL_RenderPresent(state.renderer);
}

void main_loop() {
  while (state.is_running) {
    SDL_Event event;
    SDL_WaitEvent(&event);

    switch (event.type) {
    case SDL_QUIT:
      state.is_running = false;
      break;
    case SDL_KEYDOWN:
      if (event.key.keysym.scancode == SDL_SCANCODE_Q)
        state.is_running = false;
      break;
    }

    update();
    render();
  }
}
