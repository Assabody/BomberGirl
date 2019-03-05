#include "../includes/main.h"

void renderTexture(SDL_Texture *tex, game_t *game, int x, int y, SDL_Rect *clip) {
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    if (clip != NULL) {
        dst.w = clip->w;
        dst.h = clip->h;
    } else {
        SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    }
    SDL_RenderCopy(game->sdl->renderer, tex, clip, &dst);
}

void destroyTextures(textures_t *textures) {
    if (textures) {
        if (textures->player)
            SDL_DestroyTexture(textures->player);
        if (textures->grass)
            SDL_DestroyTexture(textures->grass);
        if (textures->stone)
            SDL_DestroyTexture(textures->stone);
        if (textures->bomb)
            SDL_DestroyTexture(textures->bomb);
    }
}