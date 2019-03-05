#include "../includes/main.h"


/*
void playerDraw(game_t *game) {
    SDL_Surface *playerSurface = IMG_Load("./assets/images/sprite.png");
    SDL_Texture *pTexture = SDL_CreateTextureFromSurface(game->sdl->renderer, playerSurface);
    int iW = 40, iH = 60;
    SDL_Rect clips[4];
    if (pTexture) {
        SDL_Rect dest = {640 / 2 - playerSurface->w / 2, 480 / 2 - playerSurface->h / 2, playerSurface->w,
                         playerSurface->h};
        SDL_BlitSurface(playerSurface, NULL, SDL_GetWindowSurface(game->sdl->window), &dest);
        for (int i = 0; i < 4; ++i) {
            clips[i].x = i / 2 * iW;
            clips[i].y = i % 2 * iH;
            clips[i].w = iW;
            clips[i].h = iH;
        }
        renderTexture(pTexture, game, game->player->position.x, (game->player->position.y - 20),
                      &clips[game->player->clip]);
    } else {
        fprintf(stdout, "Échec de création de la texture (%s)\n", SDL_GetError());
    }

    SDL_FreeSurface(playerSurface);
}*/
