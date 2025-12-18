#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "math.h"
#include "simulation.h"
#include "particle.h"

struct Particle *particle_create(struct Vec2 position) {
	struct Particle *p = malloc(sizeof(struct Particle));

	if(!p) {
		fprintf(stderr, "Could not allocate particle");
		return nullptr;
	}

	p->prev = nullptr;
	p->next = nullptr;

	p->position = position;
	p->velocity = (struct Vec2){0};

	return p;
}

void particle_calculate_forces(struct Particle *p, struct Simulation *sim) {
	p->force = (struct Vec2){0};

	const struct Vec2 diff_to_prev = vec2_sub(p->prev->position, p->position);
	const struct Vec2 diff_to_next = vec2_sub(p->next->position, p->position);

	const struct Vec2 spring_force = vec2_mul(vec2_add(diff_to_prev, diff_to_next), ATTRACTION_FORCE);
	p->force = vec2_add(p->force, spring_force);

	struct Particle *other = sim->head;
	do {
		if(other != p && other != p->next && other != p->prev) {
			const float dist_sqr = vec2_dist_sqr(p->position, other->position);
			if(dist_sqr < INTERACTION_RADIUS * INTERACTION_RADIUS) {
				const float dist = sqrtf(dist_sqr);
				const struct Vec2 dir = vec2_div(vec2_sub(p->position, other->position), dist);
				const float strength = (1.0f - (dist / INTERACTION_RADIUS)) * REPULSION_FORCE;

				p->force = vec2_add(p->force, vec2_mul(dir, strength));
			}
		}

		other = other->next;
	} while(other != sim->head);

	const float margin = RENDER_PARTICLE_RADIUS * 2.0f;

	if(p->position.x < margin)			p->force.x += 1.0f;
	else if(p->position.x > 640-margin)	p->force.x -= 1.0f;

	if(p->position.y < margin)			p->force.y += 1.0f;
	else if(p->position.y > 640-margin)	p->force.y -= 1.0f;

	const struct Vec2 noise = vec2_mul((struct Vec2){
		rand() / (float)RAND_MAX - 0.5f,
		rand() / (float)RAND_MAX - 0.5f
	}, NOISE_FORCE);

	p->force = vec2_add(p->force, noise);
}

void particle_apply_physics(struct Particle *p) {
	p->velocity = vec2_add(p->velocity, p->force);
	p->velocity = vec2_mul(p->velocity, FRICTION);

	float speed_sqr = vec2_mag_sqr(p->velocity);
	if(speed_sqr > MAX_SPEED * MAX_SPEED) {
		p->velocity = vec2_set_magnitude(p->velocity, MAX_SPEED);
	}

	p->position = vec2_add(p->position, p->velocity);
}

