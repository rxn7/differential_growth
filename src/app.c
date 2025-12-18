#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>

#include "app.h"
#include "render.h"

static void app_update(struct App *app);
static void app_render(struct App *app);
static void app_handle_event(struct App *app, SDL_Event *event);

bool app_init(struct App *app) { 
    if(!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Could not initialize SDL: %s", SDL_GetError());
        return false;
    }

    app->window = SDL_CreateWindow("Differential Growth", 640, 640, SDL_WINDOW_RESIZABLE);
    if(!app->window) {
        fprintf(stderr, "Could not create window: %s", SDL_GetError());
        return false;
    }

    app->renderer = SDL_CreateRenderer(app->window, nullptr);
    if(!app->renderer) {
        fprintf(stderr, "Could not create renderer: %s", SDL_GetError());
        return false;
    }
    SDL_SetRenderLogicalPresentation(app->renderer, 640, 640, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    if(!TTF_Init()) {
        fprintf(stderr, "Could not initialize SDL_ttf: %s", SDL_GetError());
        return false;
    }

    srand(time(nullptr));

    app->is_running = true;

    if(!render_init(app->renderer)) {
        return false;
    }

    simulation_init(&app->simulation);

    return true; 
} 

void app_free(struct App *app) {
    simulation_free(&app->simulation);
    render_free();

    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    SDL_Quit();
}

void app_run(struct App *app) {
    uint64_t last_frame = SDL_GetPerformanceCounter();
    uint64_t last_simulation_step_time = last_frame;

    while(app->is_running) {
        const uint64_t now = SDL_GetPerformanceCounter();
        app->delta_time = (now - last_frame) / (float)SDL_GetPerformanceFrequency();
        last_frame = now;

        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            app_handle_event(app, &event);
        }

        if((now - last_simulation_step_time) / (float)SDL_GetPerformanceFrequency() > 1.0f / 30.0f) {
            simulation_step(&app->simulation);
            last_simulation_step_time = now;
        }

        app_update(app);
        app_render(app);
    }
}

static void app_update([[maybe_unused]] struct App *app) {
}

static void app_render(struct App *app) {
    SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
    SDL_RenderClear(app->renderer);

    render_particle_links(&app->simulation, app->renderer);
    // render_particles(&app->simulation, app->renderer);

    char buffer[32];

    snprintf(buffer, sizeof(buffer), "Particles: %u", app->simulation.particle_count);
    render_text(app->renderer, buffer, 0, 0);

    snprintf(buffer, sizeof(buffer), "FPS: %u", (uint32_t)(1.0f / app->delta_time));
    render_text(app->renderer, buffer, 0, 16);

    SDL_RenderPresent(app->renderer);
}

static void app_handle_event(struct App *app, SDL_Event *event) {
    switch(event->type) {
        case SDL_EVENT_QUIT:
            app->is_running = false;
            break;
        case SDL_EVENT_KEY_DOWN:
            switch(event->key.key) {
                case SDLK_R:
                    simulation_reset(&app->simulation);
                    break;

                case SDLK_ESCAPE:
                    app->is_running = false;
                    break;
            }
            break;
    }
}
