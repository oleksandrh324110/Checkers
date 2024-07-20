#include <algorithm>
#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_render.h>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

bool running = true;
bool dark_mode = true;
bool vsync = true;

int main(void)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    SDL_Window* window = SDL_CreateWindow("Hello SDL2!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 480, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.mod & KMOD_ALT)
                    switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_D:
                        dark_mode = !dark_mode;
                        break;
                    case SDL_SCANCODE_V:
                        vsync = !vsync;
                        break;
                    case SDL_SCANCODE_Q:
                        running = false;
                        break;
                    }
            }
        }

        dark_mode ? ImGui::StyleColorsDark()
                  : ImGui::StyleColorsLight();

        SDL_RenderSetVSync(renderer, vsync);

        ImGui_ImplSDL2_NewFrame();
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui::NewFrame();

        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("App")) {
                if (ImGui::MenuItem(dark_mode ? "Light mode" : "Dark mode", "Alt+D"))
                    dark_mode = !dark_mode;
                if (ImGui::MenuItem(vsync ? "Disable VSync" : "Enable VSync", "Alt+V"))
                    vsync = !vsync;
                if (ImGui::MenuItem("Exit", "Alt+Q"))
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