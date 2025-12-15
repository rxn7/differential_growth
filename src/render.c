#include "render.h"

static void render_line_particles(struct Particle *a, struct Particle *b, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderLine(renderer, a->x, a->y, b->x, b->y);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderPoint(renderer, a->x, a->y);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderPoint(renderer, b->x, b->y);
}

void render_particles(struct Particle *head, SDL_Renderer *renderer) {
    struct Particle *p = head;
    struct Particle *next = p->next;

    while(next) {
        render_line_particles(p, next, renderer);

        p = next;
        next = p->next;
    }

    render_line_particles(p, head, renderer);
}
