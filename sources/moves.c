#include "../includes/main.h"


void    movePlayer(game_t *game, SDL_Keycode direction) {
  if (direction == SDLK_UP) {
    printf("keyUp\n");
    if (game->player->position.y > 0 && game->map[(game->player->position.y / 40) - 1][game->player->position.x / 40] != 's') {
      game->player->position.y -= game->player->speed;
    }
    game->player->clip = 2;
  }  else if (direction == SDLK_DOWN) {
    printf("keyDown\n");
    if (game->player->position.y < (game->sdl->screenSize.y - game->player->position.w) && game->map[(game->player->position.y / 40) + 1][game->player->position.x / 40] != 's') {
      game->player->position.y += game->player->speed;
    }
    game->player->clip = 0;
  }  else if (direction == SDLK_LEFT) {
    printf("keyLeft\n");
    if (game->player->position.x > 0 && game->map[game->player->position.y / 40][(game->player->position.x / 40) - 1] != 's') {
      game->player->position.x -= game->player->speed;
    }
    game->player->clip = 3;
  }  else  if (direction == SDLK_RIGHT) {
    printf("keyRight\n");
    if (game->player->position.x < (game->sdl->screenSize.x - game->player->position.h) && game->map[game->player->position.y / 40][(game->player->position.x / 40) + 1] != 's') {
      game->player->position.x += game->player->speed;
    }
    game->player->clip = 1;
  }
}
