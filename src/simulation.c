#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "simulation.h"
#include "math.h"
#include "particle.h"

#define START_PARTICLE_COUNT 100
#define MAX_PARTICLE_COUNT 1000
#define INSERT_DISTANCE 50.0f // Distance between neighbors after which a new particle is inserted

void simulation_init(struct Simulation *sim) {
    sim->particle_count = START_PARTICLE_COUNT;
    sim->head = particle_create((struct Vec2){320, 520});

    struct Particle *last = sim->head;
    for(int i=1; i<START_PARTICLE_COUNT; ++i) {
        const float angle = 2 * PI * i / 100.0f;
        const struct Vec2 position = (struct Vec2){
            sin(angle) * 200 + 320,
            cos(angle) * 200 + 320
        };

        struct Particle *p = particle_create(position);
        particle_insert_after(p, last);

        last = p;
    }
}

void simulation_free(struct Simulation *sim) {
    struct Particle *p = sim->head;
    while(p) {
        struct Particle *next = p->next;
        free(p);
        p = next;
    }
}

void simulation_step(struct Simulation *sim, float dt) {
    struct Particle *p1 = sim->head;
    while(p1) {
        struct Particle *p2 = p1->next;
        if(p2) {
            if(sim->particle_count < MAX_PARTICLE_COUNT && dist_sqr(p1->position, p2->position) > INSERT_DISTANCE * INSERT_DISTANCE) {
                struct Vec2 mid_point = (struct Vec2){
                    (p1->position.x + p2->position.x) / 2.0f,
                    (p1->position.y + p2->position.y) / 2.0f
                };

                struct Particle *new_particle = particle_create(mid_point);
                particle_insert_after(new_particle, p1);

                ++sim->particle_count;
                printf("New node inserted %d\n", sim->particle_count);
            }
        }

        particle_update(p1, dt);
        p1 = p2;
    }
}
