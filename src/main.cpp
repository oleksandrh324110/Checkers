#include <algorithm>
#include <iostream>
#include <vector>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int main(void)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    SDL_Window *window = SDL_CreateWindow("Hello SDL3!", 720, 480, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, "opengl");

    SDL_SetRenderVSync(renderer, true);

    bool running = false;
    while (!running) {
        SDL_Event event;
        SDL_PollEvent(&event);

        switch (event.type) {
        case SDL_EVENT_QUIT:
            running = true;
            break;
        case SDL_EVENT_KEY_DOWN:
            if (event.key.key == SDLK_Q)
                running = true;
        }

        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}