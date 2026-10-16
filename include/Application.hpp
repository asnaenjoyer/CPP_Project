#pragma once

#include <SDL3/SDL.h>

#include "ExpenseManager.hpp"
#include "views/ExpenseView.hpp"

class Application
{
private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    ExpenseManager expenseManager;
    ExpenseView expenseView;

    bool running = false;

    bool init();
    void processEvents();
    void render();
    void shutdown();

public:
    Application();
    ~Application();

    int run();
};