#include "Application.hpp"

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

Application::Application()
    : expenseView(expenseManager) {}

Application::~Application()
{
    shutdown();
}

bool Application::init()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
        return false;

    window = SDL_CreateWindow("Expense Tracker", 1000, 700, SDL_WINDOW_RESIZABLE);
    if (!window)
        return false;

    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer)
        return false;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    if (!ImGui_ImplSDL3_InitForSDLRenderer(window, renderer))
        return false;

    if (!ImGui_ImplSDLRenderer3_Init(renderer))
        return false;

    return true;
}

void Application::processEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL3_ProcessEvent(&event);

        if (event.type == SDL_EVENT_QUIT ||
            (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED &&
             event.window.windowID == SDL_GetWindowID(window)))
        {
            running = false;
        }
    }
}

void Application::render()
{
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    expenseView.render();

    ImGui::Render();

    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
    SDL_RenderPresent(renderer);
}

void Application::shutdown()
{
    if (ImGui::GetCurrentContext())
    {
        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
    }

    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
}

int Application::run()
{
    if (!init())
    {
        shutdown();
        return 1;
    }

    running = true;

    while (running)
    {
        processEvents();
        render();
    }

    return 0;
}
