#pragma once

#include <SDL3/SDL_render.h>

struct Particle {
    float x;
    float y;

    struct Particle *prev;
    struct Particle *next;
};

struct Particle *particle_create(float x, float y);
void particle_destroy(struct Particle *p);
void particle_insert_after(struct Particle *p, struct Particle *after);
void particle_draw(struct Particle *p, SDL_Renderer *renderer);
