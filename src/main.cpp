#include <algorithm>
#include <iostream>
#include <vector>

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

bool running = true;
bool dark_mode = true;
bool vsync = true;

int main(void)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    SDL_Window *window = SDL_CreateWindow("Hello SDL3!", 720, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, "opengl");

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
            switch (event.type) {
            case SDL_EVENT_QUIT:
                running = false;
                break;
            case SDL_EVENT_KEY_DOWN:
                if (event.key.key == SDLK_Q)
                    running = false;
                else if (event.key.key == SDLK_D)
                    dark_mode = !dark_mode;
                else if (event.key.key == SDLK_V)
                    vsync = !vsync;
                break;
            }
        }

        dark_mode ? ImGui::StyleColorsDark()
                  : ImGui::StyleColorsLight();

        SDL_SetRenderVSync(renderer, vsync);

        ImGui_ImplSDL3_NewFrame();
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui::NewFrame();

        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("App")) {
                if (ImGui::MenuItem(dark_mode ? "Light mode" : "Dark mode", "D"))
                    dark_mode = !dark_mode;
                if (ImGui::MenuItem(vsync ? "Disable VSync" : "Enable VSync", "V"))
                    vsync = !vsync;
                if (ImGui::MenuItem("Exit", "Q"))
                    running = false;
                ImGui::EndMenu();
            }
            ImGui::SameLine(ImGui::GetWindowWidth() - 90);
            ImGui::Text("FPS: %.0f", ImGui::GetIO().Framerate);
            ImGui::EndMainMenuBar();
        }

        dark_mode
            ? SDL_SetRenderDrawColor(renderer, 0x24, 0x24, 0x24, 0xff)
            : SDL_SetRenderDrawColor(renderer, 0xdb, 0xdb, 0xdb, 0xff);
        SDL_RenderClear(renderer);
        ImGui::Render();
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);
    }

    ImGui_ImplSDL3_Shutdown();
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}