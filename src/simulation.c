#include <stdlib.h>
#include <math.h>

#include "simulation.h"
#include "math.h"
#include "particle.h"

static void check_insert(struct Simulation *sim, struct Particle *p1, const struct Particle *p2);

void simulation_init(struct Simulation *sim) {
    sim->particle_count = 0;

    for(int i=0; i<START_PARTICLE_COUNT; ++i) {
        const float angle = 2 * PI * i / (float)(START_PARTICLE_COUNT);
        const struct Vec2 position = (struct Vec2){
            sin(angle) * CIRCLE_RADIUS + 320,
            cos(angle) * CIRCLE_RADIUS + 320
        };

        struct Particle *p = particle_create(position);

        if(!sim->head) {
            ++sim->particle_count;
            sim->head = p;
            sim->tail = p;

            p->prev = p;
            p->next = p;
        } else {
            simulation_insert_particle(sim, p, sim->tail);
        }
    }
}

void simulation_free(struct Simulation *sim) {
    if(!sim->head) {
        return;
    }

    sim->tail->next = nullptr;

    struct Particle *current = sim->head;
    while(current) {
        struct Particle *next = current->next;
        free(current);
        current = next;
    }

    sim->head = nullptr;
    sim->tail = nullptr;
    sim->particle_count = 0;
    sim->particle_positions_count = 0;
}

void simulation_reset(struct Simulation *sim) {
    simulation_free(sim);
    simulation_init(sim);
}

void simulation_step(struct Simulation *sim) {
    if(!sim->head) {
        return;
    }

    struct Particle *p = sim->head;
    do {
        particle_calculate_forces(p, sim);
        p = p->next;
    } while(p != sim->head);

    p = sim->head;
    do {
        particle_apply_physics(p);
        p = p->next;
    } while(p != sim->head);

    struct Particle *stop_node = sim->head->prev;
    struct Particle *current = sim->head;
    uint32_t i=0;

    do {
        struct Particle *next = current->next;

        check_insert(sim, current, current->next);
        sim->particle_positions[i++] = (SDL_FPoint){current->position.x, current->position.y};

        if(current == stop_node) {
            break;
        }

        current = next;
    } while(current != stop_node->next);

    sim->particle_positions[i++] = sim->particle_positions[0];

    sim->particle_positions_count = i;
}

void simulation_insert_particle(struct Simulation *sim, struct Particle *p, struct Particle *after) {
	if(!p || !after) {
		return;
	}

    struct Particle *before_next = after->next;

	p->prev = after;
	p->next = before_next;

    after->next = p;
	if(before_next) {
        before_next->prev = p;
	}

    if(after == sim->tail) {
        sim->tail = p;
    }

    if(sim->head->prev != sim->tail) {
        sim->head->prev = sim->tail; 
        sim->tail->next = sim->head;
    }

    ++sim->particle_count;
}

static void check_insert(struct Simulation *sim, struct Particle *p1, const struct Particle *p2) {
    if(sim->particle_count < MAX_PARTICLE_COUNT && vec2_dist_sqr(p1->position, p2->position) > MAX_EDGE_LENGTH * MAX_EDGE_LENGTH) {
        struct Vec2 mid_point = (struct Vec2){
            (p1->position.x + p2->position.x) / 2.0f,
            (p1->position.y + p2->position.y) / 2.0f
        };

        struct Particle *new_particle = particle_create(mid_point);
        simulation_insert_particle(sim, new_particle, p1);
    }
}
