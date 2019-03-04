#include "../includes/main.h"

game_t* init() {
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
    if(!game->sdl->font) {
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
  initTextures(game);
  return game;
}

bombs_t *new_bombs(void)
{
    bombs_t* bombs = malloc(sizeof *bombs);

    if (bombs != NULL) {
        bombs->first = NULL;
        bombs->last = NULL;
    }
    return (bombs);
}

game_t *initStructs() {
    game_t *game = NULL;
    game = malloc(sizeof *game);
    sdl_t *sdl = NULL;
    sdl = malloc(sizeof *sdl);
    sdl->screenSize.x = 680;
    sdl->screenSize.y = 440;
    sdl->renderer = NULL;
    game->sdl = sdl;

    game->player = NULL;
    game->bombs = new_bombs();
    game->speed = 40;
    game->playerPosition.x = 80;
    game->playerPosition.y = 80;
    game->playerPosition.w = 40;
    game->playerPosition.h = 40;
    game->running = 1;
    game->frameCount = 0;
    game->client_sock = -1;
    game->map = mapInit();
    return (game);
}

void initTextures(game_t *game) {
    SDL_Surface *grassSurface = IMG_Load("./assets/images/grass.png");
    if (grassSurface == NULL) {
        fprintf(stderr, SDL_GetError());
        gameDestroy(game);
    } else {
        game->grass = SDL_CreateTextureFromSurface(game->sdl->renderer, grassSurface);
        SDL_FreeSurface(grassSurface);
        if (!game->grass) {
            fprintf(stderr, SDL_GetError());
            gameDestroy(game);
        }
    }

     SDL_Surface* stoneSurface = IMG_Load("./assets/images/stone.png");
     if (stoneSurface == NULL) {
       fprintf(stderr, SDL_GetError());
       gameDestroy(game);
     } else {
       game->stone = SDL_CreateTextureFromSurface(game->sdl->renderer, stoneSurface);
       SDL_FreeSurface(stoneSurface);
       if (!game->stone) {
         fprintf(stderr, SDL_GetError());
         gameDestroy(game);
       }
    }

     SDL_Surface* wallSurface = IMG_Load("./assets/images/stone.png");
     if (wallSurface == NULL) {
       fprintf(stderr, SDL_GetError());
       gameDestroy(game);
     } else {
       game->wall = SDL_CreateTextureFromSurface(game->sdl->renderer, wallSurface);
       SDL_FreeSurface(wallSurface);
       if (!game->wall) {
         fprintf(stderr, SDL_GetError());
         gameDestroy(game);
       }
    }

    SDL_Surface *bombSurface = IMG_Load("./assets/images/bombeSprite.png");
    if (bombSurface == NULL) {
        fprintf(stderr, SDL_GetError());
        gameDestroy(game);
    } else {
        game->bomb = SDL_CreateTextureFromSurface(game->sdl->renderer, bombSurface);
        SDL_Rect dest = { 640/2 - bombSurface->w/2,480/2 - bombSurface->h/2, bombSurface->w, bombSurface->h};
        SDL_BlitSurface(bombSurface,NULL,SDL_GetWindowSurface(game->sdl->window),&dest);
        for (int i = 0; i < 4; ++i){
            game->sdl->bomb_clips[i].x = i / 2 * 40;
            game->sdl->bomb_clips[i].y = i % 2 * 40;
            game->sdl->bomb_clips[i].w = 40;
            game->sdl->bomb_clips[i].h = 40;
        }
        SDL_FreeSurface(bombSurface);
        if (!game->bomb) {
            fprintf(stderr, SDL_GetError());
            gameDestroy(game);
        }
    }
}

void gameDestroy(game_t *game) {
    if (game) {
        /* if (game->player) { */
        /*     SDL_DestroyTexture(game->player); */
        /* } */
        if (game->grass) {
            SDL_DestroyTexture(game->grass);
        }
        if (game->stone) {
            SDL_DestroyTexture(game->stone);
        }
        if (game->bomb) {
             SDL_DestroyTexture(game->bomb);
        }
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
