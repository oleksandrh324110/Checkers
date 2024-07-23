#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_render.h>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

int cell_size;
bool dark_mode = true;
bool vsync = true;

void toggleDarkMode()
{
    dark_mode = !dark_mode;
    dark_mode ? ImGui::StyleColorsDark()
              : ImGui::StyleColorsLight();
}

void toggleVSync(SDL_Renderer* renderer)
{
    vsync = !vsync;
    SDL_RenderSetVSync(renderer, vsync);
}

int main(void)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    SDL_Window* window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 720 + 19, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    cell_size = 720 / 8;

    SDL_RenderSetVSync(renderer, vsync);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    dark_mode ? ImGui::StyleColorsDark()
              : ImGui::StyleColorsLight();

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    bool running = true;
    while (running) {
        for (SDL_Event event; SDL_PollEvent(&event);) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    cell_size = event.window.data1 / 8;
                    SDL_SetWindowSize(window, cell_size * 8, cell_size * 8 + 19);
                }
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_D:
                    toggleDarkMode();
                    break;
                case SDL_SCANCODE_V:
                    toggleVSync(renderer);
                    break;
                case SDL_SCANCODE_Q:
                    running = false;
                    break;
                }
            }
        }

        ImGui_ImplSDL2_NewFrame();
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui::NewFrame();

        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("App")) {
                if (ImGui::MenuItem(dark_mode ? "Light mode" : "Dark mode", "D"))
                    toggleDarkMode();
                if (ImGui::MenuItem(vsync ? "Disable VSync" : "Enable VSync", "V"))
                    toggleVSync(renderer);
                if (ImGui::MenuItem("Exit", "Q"))
                    running = false;
                ImGui::EndMenu();
            }
            ImGui::SameLine(ImGui::GetWindowWidth() - 90);
            ImGui::Text("FPS: %.0f", ImGui::GetIO().Framerate);
            ImGui::EndMainMenuBar();
        }

        dark_mode ? SDL_SetRenderDrawColor(renderer, 0x24, 0x24, 0x24, 0xff)
                  : SDL_SetRenderDrawColor(renderer, 0xdb, 0xdb, 0xdb, 0xff);
        SDL_RenderClear(renderer);

        for (uint8_t i = 0; i < 8; i++) {
            for (uint8_t j = (i + 1) % 2; j < 8; j += 2) {
                SDL_Rect rect = { j * cell_size, i * cell_size + 19, cell_size, cell_size };
                SDL_SetRenderDrawColor(renderer, 0xc3, 0x84, 0x26, 0xff);
                SDL_RenderFillRect(renderer, &rect);
            }
        }

        ImGui::Render();
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);
    }

    ImGui_ImplSDL2_Shutdown();
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
