#pragma once

#include <SDL3/SDL_render.h>

#include "simulation.h"

struct App {
    bool is_running;
    SDL_Window *window;
    SDL_Renderer *renderer;

    struct Simulation simulation;
};

bool app_init(struct App *app);
void app_free(struct App *app);
void app_run(struct App *app);
