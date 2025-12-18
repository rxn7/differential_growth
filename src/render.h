#pragma once

#include <SDL3_ttf/SDL_ttf.h>
#include "simulation.h"

bool render_init(SDL_Renderer *renderer);
void render_free();
void render_particles(struct Simulation *sim, SDL_Renderer *renderer);
void render_particle_links(struct Simulation *sim, SDL_Renderer *renderer);
void render_text(SDL_Renderer *renderer, const char *text, int x, int y);
