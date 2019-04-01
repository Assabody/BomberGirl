#include "../includes/main.h"

sdl_t *initSdl() {
    sdl_t *sdl = malloc(sizeof *sdl);
    sdl->frameCount = 0;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, SDL_GetError());
        return NULL;
    }
    sdl->window = SDL_CreateWindow(
            "Bombergirl", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_SIZE_X,
            SCREEN_SIZE_Y,
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

void clearSdl(sdl_t *sdl) {
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
        TTF_Quit();
        SDL_Quit();
        free(sdl);
    }
    sdl = NULL;
    puts("Sdl cleared");
}

void renderTexture(SDL_Texture *tex, sdl_t *sdl, int x, int y, SDL_Rect *clip) {
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    if (clip != NULL) {
        dst.w = clip->w;
        dst.h = clip->h;
    } else {
        SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    }
    SDL_RenderCopy(sdl->renderer, tex, clip, &dst);
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
        if (textures->brick)
            SDL_DestroyTexture(textures->brick);
        if (textures->bomb)
            SDL_DestroyTexture(textures->bomb);
        if (textures->menu)
            SDL_DestroyTexture(textures->menu);
        if (textures->flame)
            SDL_DestroyTexture(textures->flame);
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
    SDL_Surface *menuSurface = IMG_Load("./assets/images/menuBackground.png");
    if (!menuSurface) {
        fprintf(stderr, SDL_GetError());
    } else {
        textures->menu = SDL_CreateTextureFromSurface(sdl->renderer, menuSurface);
        SDL_FreeSurface(menuSurface);
        if (!textures->menu) {
            fprintf(stderr, SDL_GetError());
        }
    }


    SDL_Surface *grassSurface = IMG_Load("./assets/images/grass.jpg");
    if (!grassSurface) {
        fprintf(stderr, SDL_GetError());
    } else {
        textures->grass = SDL_CreateTextureFromSurface(sdl->renderer, grassSurface);
        SDL_FreeSurface(grassSurface);
        if (!textures->grass) {
            fprintf(stderr, SDL_GetError());
        }
    }

    SDL_Surface *stoneSurface = IMG_Load("./assets/images/stone.jpg");
    if (!stoneSurface) {
        fprintf(stderr, SDL_GetError());
    } else {
        textures->stone = SDL_CreateTextureFromSurface(sdl->renderer, stoneSurface);
        SDL_FreeSurface(stoneSurface);
        if (!textures->stone) {
            fprintf(stderr, SDL_GetError());
        }
    }

    SDL_Surface *brickSurface = IMG_Load("./assets/images/brick.jpg");
    if (!stoneSurface) {
        fprintf(stderr, SDL_GetError());
    } else {
        textures->brick = SDL_CreateTextureFromSurface(sdl->renderer, brickSurface);
        SDL_FreeSurface(brickSurface);
        if (!textures->brick) {
            fprintf(stderr, SDL_GetError());
        }
    }

    SDL_Surface *flameSurface = IMG_Load("./assets/images/flame.png");
    if (!flameSurface) {
        fprintf(stderr, SDL_GetError());
    } else {
        textures->flame = SDL_CreateTextureFromSurface(sdl->renderer, flameSurface);
        SDL_FreeSurface(flameSurface);
        if (!textures->flame) {
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
