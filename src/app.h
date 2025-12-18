#pragma once

#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "simulation.h"

struct App {
    bool is_running;
    float delta_time;

    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;

    struct Simulation simulation;
};

bool app_init(struct App *app);
void app_free(struct App *app);
void app_run(struct App *app);
