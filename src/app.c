#include <stdio.h>

#include "app.h"
#include "SDL3/SDL_timer.h"

static void app_update(struct App *app, float delta_time);
static void app_render(struct App *app);

bool app_init(struct App *app) { 
    if(!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Could not initialize SDL: %s", SDL_GetError());
        return false;
    }

    app->window = SDL_CreateWindow("Differential Growth", 640, 480, 0);
    if(!app->window) {
        fprintf(stderr, "Could not create window: %s", SDL_GetError());
        return false;
    }

    app->renderer = SDL_CreateRenderer(app->window, nullptr);
    if(!app->renderer) {
        fprintf(stderr, "Could not create renderer: %s", SDL_GetError());
        return false;
    }

    app->is_running = true;

    return true; 
} 

void app_free(struct App *app) {
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    SDL_Quit();
}

void app_run(struct App *app) {
    uint64_t last_frame = SDL_GetPerformanceCounter();

    while(app->is_running) {
        const uint64_t now = SDL_GetPerformanceCounter();
        const float delta_time = (now - last_frame) / (float)SDL_GetPerformanceFrequency();
        last_frame = now;

        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_EVENT_QUIT) {
                app->is_running = false;
            }
        }

        app_update(app, delta_time);
        app_render(app);
    }
}

static void app_update(struct App *app, float delta_time) {
}

static void app_render(struct App *app) {
    SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
    SDL_RenderClear(app->renderer);

    SDL_RenderPresent(app->renderer);
}
