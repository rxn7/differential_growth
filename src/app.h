#pragma once

#include <SDL3/SDL.h>

struct App {
    bool is_running;
    SDL_Window *window;
    SDL_Renderer *renderer;
};

bool app_init(struct App *app);
void app_free(struct App *app);
void app_run(struct App *app);
