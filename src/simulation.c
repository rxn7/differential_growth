#include <stdlib.h>
#include <math.h>

#include "simulation.h"
#include "particle.h"

void simulation_init(struct Simulation *sim) {
    constexpr float PI = 3.14159265358979323846f;

    sim->head = particle_create(320, 520);
    struct Particle *last = sim->head;
    for(int i=0; i<100; ++i) {
        const float angle = 2 * PI * i / 100.0f;
        const float x = sin(angle) * 200 + 320;
        const float y = cos(angle) * 200 + 320;

        struct Particle *p = particle_create(x, y);
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

void simulation_step(struct Simulation *sim) {
}
