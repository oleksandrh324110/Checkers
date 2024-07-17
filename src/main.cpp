#include <algorithm>
#include <iostream>
#include <vector>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

struct Mouse
{
    float x, y;
};

float map(float value, float start1, float stop1, float start2, float stop2)
{
    return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
}

int main(void)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    SDL_Window *window = SDL_CreateWindow("Hello SDL3!", 720, 480, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, "opengl");

    SDL_SetRenderVSync(renderer, true);

    Mouse mouse;

    bool running = false;
    while (!running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_EVENT_QUIT:
                running = true;
                break;
            case SDL_EVENT_KEY_DOWN:
                if (event.key.key == SDLK_Q)
                    running = true;
                break;
            }
        }

        SDL_GetMouseState(&mouse.x, &mouse.y);
        Uint8 brightness = map(mouse.x, 0, 720, 0, 255);

        SDL_SetRenderDrawColor(renderer, brightness, brightness, brightness, 0xff);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}