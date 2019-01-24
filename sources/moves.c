#include "../includes/main.h"

void    movePlayer(game_t *game, SDL_Keycode direction) {
  if (direction == SDLK_UP) {
    printf("keyUp\n");
    printf("PosY: %i\n", game->playerPosition.y);
    if (game->playerPosition.y > 0) {
      game->playerPosition.y -= 40;
    printf("PosY: %i\n", game->playerPosition.y);
    }
  }  else if (direction == SDLK_DOWN) {
    printf("keyDown\n");
    printf("PosY: %i\n", game->playerPosition.y);
    if (game->playerPosition.y < (game->screenSize.y - game->playerPosition.w)) {
      game->playerPosition.y += 40;
    }
  }  else if (direction == SDLK_LEFT) {
    printf("keyLeft\n");
    printf("PosX: %i\n", game->playerPosition.x);
    if (game->playerPosition.x > 0) {
      game->playerPosition.x -= 40;
    }
  }  else  if (direction == SDLK_RIGHT) {
    printf("keyRight\n");
    printf("PosX: %i\n", game->playerPosition.x);
    if (game->playerPosition.x < (game->screenSize.x - game->playerPosition.h)) {
      game->playerPosition.x += 40;
    }
  } else {
    fprintf(stderr, "Direction inconnue\n /");
  }
}
