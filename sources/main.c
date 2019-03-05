#include "../includes/main.h"

game_t *init() {
    game_t *game = initStructs();

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, SDL_GetError());
        gameDestroy(game);
        return NULL;
    }
    game->sdl->window = SDL_CreateWindow("Bombergirl", SDL_WINDOWPOS_UNDEFINED,
                                         SDL_WINDOWPOS_UNDEFINED,
                                         game->sdl->screenSize.x,
                                         game->sdl->screenSize.y,
                                         SDL_WINDOW_SHOWN);

    TTF_Init();
    game->sdl->font = TTF_OpenFont("./assets/Gameplay.ttf", 20);
    if (!game->sdl->font) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }
    if (game->sdl->window) {
        game->sdl->renderer = SDL_CreateRenderer(game->sdl->window, -1, SDL_RENDERER_ACCELERATED);
        if (!game->sdl->renderer) {
            fprintf(stderr, SDL_GetError());
            gameDestroy(game);
            return NULL;
        }
        SDL_SetRenderDrawColor(game->sdl->renderer, 50, 50, 50, 255);
    } else {
        fprintf(stderr, SDL_GetError());
        gameDestroy(game);
        return NULL;
    }
    game->textures = initTextures(game->sdl);
    return game;
}

game_t *initStructs() {
    game_t *game = NULL;
    game = malloc(sizeof *game);
    if (game == NULL) {
        return NULL;
    }

    sdl_t *sdl = NULL;
    sdl = malloc(sizeof *sdl);
    if (sdl == NULL) {
        free(game);
        return NULL;
    }

    player_t *player = NULL;
    player = malloc(sizeof *player);
    if (sdl == NULL) {
        free(game);
        free(sdl);
        return NULL;
    }
    /*game->textures = initTextures(game->sdl);
    if (!game->textures) {
        return NULL;
    }*/
    sdl->screenSize.x = 680;
    sdl->screenSize.y = 440;
    sdl->renderer = NULL;
    game->sdl = sdl;

    game->player = player;
    game->bombs = initBombs();
    game->player->speed = 40;
    game->player->position.x = 80;
    game->player->position.y = 80;
    game->player->position.w = 40;
    game->player->position.h = 40;
    game->player->clip = 0;
    game->running = 1;
    game->client_sock = -1;
    game->map = mapInit();
    return (game);
}

textures_t *initTextures(sdl_t *sdl) {
    textures_t *textures = malloc(sizeof *textures);

    if (textures == NULL) {
        return NULL;
    }
    SDL_Surface *grassSurface = IMG_Load("./assets/images/grass.png");
    if (grassSurface == NULL) {
        fprintf(stderr, SDL_GetError());
    } else {
        textures->grass = SDL_CreateTextureFromSurface(sdl->renderer, grassSurface);
        SDL_FreeSurface(grassSurface);
        if (!textures->grass) {
            fprintf(stderr, SDL_GetError());
        }
    }

    SDL_Surface *stoneSurface = IMG_Load("./assets/images/stone.png");
    if (stoneSurface == NULL) {
        fprintf(stderr, SDL_GetError());
    } else {
        textures->stone = SDL_CreateTextureFromSurface(sdl->renderer, stoneSurface);
        SDL_FreeSurface(stoneSurface);
        if (!textures->stone) {
            fprintf(stderr, SDL_GetError());
        }
    }

    SDL_Surface *bombSurface = IMG_Load("./assets/images/bombeSprite.png");
    if (bombSurface == NULL) {
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
    if (playerSurface == NULL) {
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

void gameDestroy(game_t *game) {
    if (game) {
        destroyTextures(game->textures);
        if (game->sdl) {
            if (game->sdl->renderer) {
                SDL_DestroyRenderer(game->sdl->renderer);
            }
            if (game->sdl->window) {
                SDL_DestroyWindow(game->sdl->window);
            }
            if (game->sdl->font) {
                TTF_CloseFont(game->sdl->font);
            }
            free(game->sdl);
        }
        TTF_Quit();
        SDL_Quit();
        free(game);
    }
}

int main() {
    game_t *game = init();
    if (game == NULL)
        return (EXIT_FAILURE);
    while (game->running) {
        menuWindow(game);
    }
    gameDestroy(game);
    return (EXIT_SUCCESS);
}
