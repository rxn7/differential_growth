#pragma once

#include <SDL3/SDL_render.h>
#include "particle.h"

struct Simulation {
    uint32_t particle_count;
    struct Particle *head;
};

void simulation_init(struct Simulation *sim);
void simulation_free(struct Simulation *sim);
void simulation_step(struct Simulation *sim, float dt);
