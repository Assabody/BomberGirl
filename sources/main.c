#include "../includes/main.h"

game_t* init() {
  game_t *game = initStructs();
  
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, SDL_GetError());
    gameDestroy(game);
    return NULL;
  }
  game->pWindow = SDL_CreateWindow("Bombergirl", SDL_WINDOWPOS_UNDEFINED,
				   SDL_WINDOWPOS_UNDEFINED,
				   game->screenSize.x,
				   game->screenSize.y,
				   SDL_WINDOW_SHOWN);
  if (game->pWindow) {
    game->renderer = SDL_CreateRenderer(game->pWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!game->renderer) {
      fprintf(stderr, SDL_GetError());
      gameDestroy(game);
      return NULL;
    }
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
  } else {
    fprintf(stderr, SDL_GetError());
    gameDestroy(game);
    return NULL;
  }
  initTextures(game);
  return game;
}

game_t *initStructs() {
    game_t *game = NULL;
    game = malloc(sizeof(game_t));
    game->renderer = NULL;
    game->player = NULL;
    game->bomb = NULL;
    game->pWindow = NULL;
    game->speed = 40;
    game->screenSize.x = 680;
    game->screenSize.y = 440;
    game->playerPosition.x = 80;
    game->playerPosition.y = 80;
    game->playerPosition.w = 40;
    game->playerPosition.h = 40;
    game->running = 1;
    game->frameCount = 0;
    game->map = mapInit();
    return (game);
}

void initTextures(game_t *game) {
    SDL_Surface *grassSurface = IMG_Load("./assets/images/grass.png");
    if (grassSurface == NULL) {
        fprintf(stderr, SDL_GetError());
        gameDestroy(game);
    } else {
        game->grass = SDL_CreateTextureFromSurface(game->renderer, grassSurface);
        if (!game->grass) {
            fprintf(stderr, SDL_GetError());
            gameDestroy(game);
        }
        SDL_FreeSurface(grassSurface);
    }

     SDL_Surface* stoneSurface = IMG_Load("./assets/images/stone.png");
     if (stoneSurface == NULL) {
       fprintf(stderr, SDL_GetError());
       gameDestroy(game);
     } else {
       game->stone = SDL_CreateTextureFromSurface(game->renderer, stoneSurface);
       if (!game->stone) { 
         fprintf(stderr, SDL_GetError()); 
         gameDestroy(game); 
       } 
       SDL_FreeSurface(stoneSurface);
    }

     SDL_Surface* wallSurface = IMG_Load("./assets/images/stone.png");
     if (wallSurface == NULL) {
       fprintf(stderr, SDL_GetError());
       gameDestroy(game);
     } else {
       game->wall = SDL_CreateTextureFromSurface(game->renderer, wallSurface);
       if (!game->wall) { 
         fprintf(stderr, SDL_GetError()); 
         gameDestroy(game); 
       } 
       SDL_FreeSurface(wallSurface);
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
        /* if (game->bomb->bombTexture) { */
        /*     SDL_DestroyTexture(game->bomb->bombTexture); */
        /* } */
        if (game->renderer) {
            SDL_DestroyRenderer(game->renderer);
        }
        if (game->pWindow) {
            SDL_DestroyWindow(game->pWindow);
        }
        SDL_Quit();
        free(game);
    }
}

int main() {
    game_t *game = init();
    Uint32 frameStart;
    int frameTime;
    SDL_SetRenderDrawColor(game->renderer, 50, 50, 50, 255);
    game->useClip = 0;
    while (game->running) {
        frameStart = SDL_GetTicks();
        gameDraw(game);
        checkEvents(game);
	SDL_RenderPresent(game->renderer);
        frameTime = SDL_GetTicks() - frameStart;
        if (TICKS_PER_FRAME > frameTime)
            SDL_Delay(TICKS_PER_FRAME - frameTime);
        game->frameCount++;
        //printf("FPS %d\n", game->frameCount);
    }
    gameDestroy(game);
    return (EXIT_SUCCESS);
}
