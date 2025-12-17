#pragma once

#include <SDL3/SDL_render.h>
#include "math.h"

// constexpr float PARTICLE_RADIUS = 3.0f;
#define PARTICLE_RADIUS 3.0f

struct Particle {
    struct Vec2 position;
    struct Vec2 velocity;
    struct Vec2 acceleration;

    struct Particle *prev;
    struct Particle *next;
};

struct Particle *particle_create(struct Vec2 position);
void particle_destroy(struct Particle *p);
void particle_insert_after(struct Particle *p, struct Particle *after);
void particle_update(struct Particle *p, float dt);
void particle_draw(struct Particle *p, SDL_Renderer *renderer);
