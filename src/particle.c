#include <stdlib.h>
#include <stdio.h>

#include "particle.h"
#include "SDL3/SDL_render.h"

struct Particle *particle_create(float x, float y) {
	struct Particle *p = malloc(sizeof(struct Particle));

	if(!p) {
		fprintf(stderr, "Could not allocate particle");
		return nullptr;
	}

	p->prev = nullptr;
	p->next = nullptr;

	p->x = x;
	p->y = y;

	return p;
}

void particle_destroy(struct Particle *p) {
	if(!p) {
		fprintf(stderr, "Tried to free nullptr particle");
		return;
	}

	if(p->prev) {
		p->prev->next = p->next;
	}

	if(p->next) {
		p->next->prev = p->prev;
	}

	free(p);
}

void particle_insert_after(struct Particle *p, struct Particle *after) {
	if(!after) {
		fprintf(stderr, "Tried to insert particle after nullptr");
		return;
	}

	if(!p) {
		fprintf(stderr, "Tried to insert nullptr particle");
		return;
	}

	p->prev = after;
	p->next = after->next;

	if(after->next) {
		after->next->prev = p;
	}

	after->next = p;
}

void particle_draw(struct Particle *p, SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderPoint(renderer, p->x, p->y);
}
