#include "../includes/main.h"


void checkEvents(game_t *game) {
    SDL_Event event;
     if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
	printf("Vous quittez le jeu\n");
	game->running = 0;
      }
      if (event.type == SDL_KEYDOWN) {
	switch (event.key.keysym.sym) {
	case SDLK_SPACE:
	  bombeDraw(game);
	  printf("BOMBE %d %d\n", game->bomb->position.x, game->bomb->position.y);
	  break;
	case SDLK_ESCAPE:
	  game->running = 0;
	  printf("Vous quittez le jeu\n");
	  break;
	case SDLK_UP:
	case SDLK_DOWN:
	case SDLK_LEFT:
	case SDLK_RIGHT:
	  movePlayer(game, event.key.keysym.sym);
	  send_message(game->client_sock, SDL_GetKeyName(event.key.keysym.sym));
	  read_message(game->client_sock);
	  break;
	default:
	  fprintf(stderr, "Touche inconnue\n");
	  break;
	}
      }     
    }
    playerDraw(game);
}

/* void initBombe(game_t *game, int seconds) { */
/*     bomb_t *bomb; */
/*     bomb = malloc(sizeof(bomb_t)); */
/*     bomb->position.x = game->playerPosition.x; */
/*     bomb->position.y = game->playerPosition.y; */
/*     bomb->position.w = 32; */
/*     bomb->position.h = 32; */
/*     bomb->duration = seconds * FPS; */
/*     game->bomb = bomb; */
/* } */
