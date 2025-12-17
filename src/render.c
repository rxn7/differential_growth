#include <SDL3_gfxPrimitives.h>
#include "render.h"

static void render_line_particles(struct Particle *a, struct Particle *b, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderLine(renderer, a->position.x, a->position.y, b->position.x, b->position.y);
}

void render_particles(struct Particle *head, SDL_Renderer *renderer) {
    struct Particle *p = head;

    while(p) {
        filledCircleRGBA(renderer, p->position.x, p->position.y, PARTICLE_RADIUS, 255, 0, 0, 255);

        if(p->next) {
            render_line_particles(p, p->next, renderer);
        } else {
            render_line_particles(p, head, renderer);
        }

        p = p->next;
    }
}
