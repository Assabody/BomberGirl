#include "../includes/main.h"


int    checkEvents(game_t *game)
{
  SDL_Event event;
  int	quit = 1;

  if (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      printf("Vous quittez le jeu\n");
      quit = 0;
    }
    if (event.type == SDL_KEYDOWN) {
      switch (event.key.keysym.sym) {
      case SDLK_SPACE:
	printf("BOMBE\n");
	initBombe(game);
	break;
      case SDLK_ESCAPE:
	quit = 0;
	printf("Vous quittez le jeu\n");
	break;
      case SDLK_UP:
      case SDLK_DOWN:
      case SDLK_LEFT:
      case SDLK_RIGHT:
	movePlayer(game, event.key.keysym.sym);
	break;
      default:
	fprintf(stderr, "Touche inconnue\n");
	break;
      }
    }

  }
  return (quit);
}

void	initBombe(game_t *game)
{
  SDL_Surface* bombeSurface = IMG_Load("./assets/images/bombe.png");
  if (bombeSurface == NULL) {
    fprintf(stderr, SDL_GetError());
    gameDestroy(game);
  } else {
    game->bombe = SDL_CreateTextureFromSurface(game->renderer, bombeSurface);
    if (!game->bombe) {
      fprintf(stderr, SDL_GetError());
      gameDestroy(game);
    }
    SDL_FreeSurface(bombeSurface);
  }
  game->bombeActive = 1;
  game->bombeDuration = 260;
  game->oldPlayerPosition.x = game->playerPosition.x;
  game->oldPlayerPosition.y = game->playerPosition.y;
}
