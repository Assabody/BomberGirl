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
  } else {
    fprintf(stderr, SDL_GetError());
    gameDestroy(game);
    return NULL;
  }
  initTextures(game);
  return game;
}

game_t	*initStructs()
{
  game_t *game = NULL;
  game = malloc(sizeof(game_t));
  game->renderer = NULL;
  game->player = NULL;
  game->bombe = NULL;
  game->pWindow = NULL;
  game->speed = 5;
  game->screenSize.x = 640;
  game->screenSize.y = 480;
  game->playerPosition.x = 40;
  game->playerPosition.y = 40;
  game->playerPosition.w = 40;
  game->playerPosition.h = 40;
  game->bombePosition.w = 40;
  game->bombePosition.h = 40;
  return (game);
}

void	initTextures(game_t *game)
{
 SDL_Surface* grassSurface = IMG_Load("./assets/images/grass.png");
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

  /* SDL_Surface* stoneSurface = IMG_Load("./assets/images/stone.png"); */
  /* if (stoneSurface == NULL) { */
  /*   fprintf(stderr, SDL_GetError()); */
  /*   gameDestroy(game); */
  /* } else { */
  /*   game->stone = SDL_CreateTextureFromSurface(game->renderer, stoneSurface); */
  /*   if (!game->stone) { */
  /*     fprintf(stderr, SDL_GetError()); */
  /*     gameDestroy(game); */
  /*   } */
  /*   SDL_FreeSurface(stoneSurface); */
  /* } */

  SDL_Surface* playerSurface = IMG_Load("./assets/images/bombergirl.png");
  if (playerSurface == NULL) {
    fprintf(stderr, SDL_GetError());
    gameDestroy(game);
  } else {
    game->player = SDL_CreateTextureFromSurface(game->renderer, playerSurface);
    if (!game->player) {
      fprintf(stderr, SDL_GetError());
      gameDestroy(game);
    }
    SDL_FreeSurface(playerSurface);
  }  
}

void	gameDestroy(game_t *game)
{
  if (game) {
    if (game->player) {
      SDL_DestroyTexture(game->player);
    }
    if (game->grass) {
      SDL_DestroyTexture(game->grass);
    }
    if (game->stone) {
      SDL_DestroyTexture(game->stone);
    }
    if (game->bombe) {
      SDL_DestroyTexture(game->bombe);
    }
    
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

int main()
{
  int	quit = 1;
  game_t *game = init();

  SDL_SetRenderDrawColor(game->renderer, 50, 50, 50, 255);
  while (quit != 0)
    {
      gameDraw(game);
      quit = checkEvents(game);
    }
  gameDestroy(game);
  return (EXIT_SUCCESS);
}
