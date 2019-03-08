#include "../includes/main.h"

sdl_t *initSdl(int width, int height) {
    sdl_t *sdl = malloc(sizeof *sdl);

    sdl->screenSize.x = width;
    sdl->screenSize.y = height;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, SDL_GetError());
        return NULL;
    }
    sdl->window = SDL_CreateWindow(
            "Bombergirl", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            sdl->screenSize.x,
            sdl->screenSize.y,
            SDL_WINDOW_SHOWN);

    if (sdl->window) {
        sdl->renderer = SDL_CreateRenderer(sdl->window, -1, SDL_RENDERER_ACCELERATED);
        if (!sdl->renderer) {
            fprintf(stderr, SDL_GetError());
            SDL_DestroyWindow(sdl->window);
            return NULL;
        }
        //SDL_SetRenderDrawColor(sdl->renderer, 50, 50, 50, 255);
    } else {
        fprintf(stderr, SDL_GetError());
        return NULL;
    }

    TTF_Init();
    sdl->font = TTF_OpenFont("./assets/Gameplay.ttf", 20);
    if (!sdl->font) {
        fprintf(stderr, TTF_GetError());
        SDL_DestroyWindow(sdl->window);
        SDL_DestroyRenderer(sdl->renderer);
        return NULL;
    }
    return sdl;
}

void clearSdl(sdl_t *sdl)
{
    puts("Clearing sdl");
    if (sdl) {
        if (sdl->renderer) {
            SDL_DestroyRenderer(sdl->renderer);
        }
        if (sdl->window) {
            SDL_DestroyWindow(sdl->window);
        }
        if (sdl->font) {
            TTF_CloseFont(sdl->font);
        }
        free(sdl);
    }
    sdl = NULL;
    puts("Sdl cleared");
}

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

void clearTextures(textures_t *textures) {
    puts("Clearing textures");
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
    free(textures);
    textures = NULL;
    puts("Textures cleared");
}

textures_t *initTextures(sdl_t *sdl) {
    textures_t *textures = malloc(sizeof *textures);
    if (!textures) {
        return NULL;
    }
    SDL_Surface *grassSurface = IMG_Load("./assets/images/grass.png");
    if (!grassSurface) {
        fprintf(stderr, SDL_GetError());
    } else {
        textures->grass = SDL_CreateTextureFromSurface(sdl->renderer, grassSurface);
        SDL_FreeSurface(grassSurface);
        if (!textures->grass) {
            fprintf(stderr, SDL_GetError());
        }
    }

    SDL_Surface *stoneSurface = IMG_Load("./assets/images/stone.png");
    if (!stoneSurface) {
        fprintf(stderr, SDL_GetError());
    } else {
        textures->stone = SDL_CreateTextureFromSurface(sdl->renderer, stoneSurface);
        SDL_FreeSurface(stoneSurface);
        if (!textures->stone) {
            fprintf(stderr, SDL_GetError());
        }
    }

    SDL_Surface *bombSurface = IMG_Load("./assets/images/bombeSprite.png");
    if (!bombSurface) {
        fprintf(stderr, SDL_GetError());
    } else {
        textures->bomb = SDL_CreateTextureFromSurface(sdl->renderer, bombSurface);
        SDL_Rect dest = {640 / 2 - bombSurface->w / 2, 480 / 2 - bombSurface->h / 2, bombSurface->w, bombSurface->h};
        SDL_BlitSurface(bombSurface, NULL, SDL_GetWindowSurface(sdl->window), &dest);
        for (int i = 0; i < 4; ++i) {
            textures->bomb_clips[i].x = i / 2 * 40;
            textures->bomb_clips[i].y = i % 2 * 40;
            textures->bomb_clips[i].w = 40;
            textures->bomb_clips[i].h = 40;
        }
        SDL_FreeSurface(bombSurface);
        if (!textures->bomb) {
            fprintf(stderr, SDL_GetError());
        }
    }

    SDL_Surface *playerSurface = IMG_Load("./assets/images/sprite.png");
    int iW = 40, iH = 60;
    if (!playerSurface) {
        fprintf(stderr, SDL_GetError());
    } else {
        textures->player = SDL_CreateTextureFromSurface(sdl->renderer, playerSurface);
        SDL_Rect dest = {640 / 2 - playerSurface->w / 2, 480 / 2 - playerSurface->h / 2, playerSurface->w,
                         playerSurface->h};
        SDL_BlitSurface(playerSurface, NULL, SDL_GetWindowSurface(sdl->window), &dest);
        for (int i = 0; i < 4; ++i) {
            textures->player_clips[i].x = i / 2 * iW;
            textures->player_clips[i].y = i % 2 * iH;
            textures->player_clips[i].w = iW;
            textures->player_clips[i].h = iH;
        }
        SDL_FreeSurface(playerSurface);
    }
    return textures;
}
