#include <SDL3_gfxPrimitives.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>

#include "render.h"
#include "particle.h"

static const uint8_t font_data[] = {
#embed "../assets/font.ttf"
};

static TTF_Font *font;

bool render_init([[maybe_unused]] SDL_Renderer *renderer) {
    SDL_IOStream *font_rw = SDL_IOFromConstMem(font_data, sizeof(font_data));
    font = TTF_OpenFontIO(font_rw, true, 16);

    if(!font) {
        fprintf(stderr, "Could not load font: %s", SDL_GetError());
        return false;
    }

    return true;
}

void render_free() {
    TTF_CloseFont(font);
}

void render_text(SDL_Renderer *renderer, const char *text, int x, int y) {
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, 0, (SDL_Color){255, 255, 255, 255});
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    const SDL_FRect rect = {x, y, surface->w, surface->h};
    SDL_RenderTexture(renderer, texture, nullptr, &rect);
    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}

void render_particles(struct Simulation *sim, SDL_Renderer *renderer) {
    struct Particle *p = sim->head;

    do {
        filledCircleRGBA(renderer, p->position.x, p->position.y, RENDER_PARTICLE_RADIUS, 255, 0, 0, 255);
        p = p->next;
    } while(p != sim->head);
}

void render_particle_links(struct Simulation *sim, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderLines(renderer, sim->particle_positions, sim->particle_positions_count);
}
