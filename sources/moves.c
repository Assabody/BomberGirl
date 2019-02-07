#include "../includes/main.h"


void    movePlayer(game_t *game, SDL_Keycode direction) {  
  if (direction == SDLK_UP) {
    printf("keyUp\n");
    printf("PosY: %i\n", game->playerPosition.y);
    if (game->playerPosition.y > 0 && game->map[(game->playerPosition.y / 40) - 1][game->playerPosition.x / 40] != 's') {
      printf("%i", game->playerPosition.y);
      game->playerPosition.y -= game->speed;
      printf("PosY: %i\n", game->playerPosition.y);
      printf("MAP position: %c\n", game->map[0][2]);
    }
  }  else if (direction == SDLK_DOWN) {
    printf("keyDown\n");
    printf("PosY: %i\n", game->playerPosition.y);
    if (game->playerPosition.y < (game->screenSize.y - game->playerPosition.w) && game->map[(game->playerPosition.y / 40) + 1][game->playerPosition.x / 40] != 's') {
      game->playerPosition.y += game->speed;
    }
  }  else if (direction == SDLK_LEFT) {
    printf("keyLeft\n");
    printf("PosX: %i\n", game->playerPosition.x);
    if (game->playerPosition.x > 0 && game->map[game->playerPosition.y / 40][(game->playerPosition.x / 40) - 1] != 's') {
      game->playerPosition.x -= game->speed;
    }
  }  else  if (direction == SDLK_RIGHT) {
    printf("keyRight\n");
    printf("PosX: %i\n", game->playerPosition.x);
    if (game->playerPosition.x < (game->screenSize.x - game->playerPosition.h) && game->map[game->playerPosition.y / 40][(game->playerPosition.x / 40) + 1] != 's') {
      game->playerPosition.x += game->speed;
    }
  } else {
    fprintf(stderr, "Direction inconnue\n /");
  }
}
