#pragma once

#include "math.h"

struct Simulation;

struct Particle {
    struct Vec2 position;
    struct Vec2 velocity;
    struct Vec2 force;

    struct Particle *prev;
    struct Particle *next;
};

struct Particle *particle_create(struct Vec2 position);
void particle_calculate_forces(struct Particle *p, struct Simulation *sim);
void particle_apply_physics(struct Particle *p);
