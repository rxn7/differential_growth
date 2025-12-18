#pragma once

#include <SDL3/SDL_render.h>
#include "SDL3/SDL_rect.h"

#include "particle.h"
#include "config.h"

struct Simulation {
    uint32_t particle_count;

    struct Particle *head, *tail;

    uint32_t particle_positions_count;
    SDL_FPoint particle_positions[MAX_PARTICLE_COUNT + 1];
};

void simulation_init(struct Simulation *sim);
void simulation_free(struct Simulation *sim);
void simulation_reset(struct Simulation *sim);
void simulation_step(struct Simulation *sim);
void simulation_insert_particle(struct Simulation *sim, struct Particle *p, struct Particle *after);
