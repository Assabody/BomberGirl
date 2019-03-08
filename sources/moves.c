#include "../includes/main.h"


void    movePlayer(game_t *game, SDL_Keycode direction) {
  if (direction == SDLK_UP) {
    printf("keyUp\n");
    if (game->player->y_pos > 0 && game->map[(game->player->y_pos / 40) - 1][game->player->x_pos / 40] != 's') {
      game->player->y_pos -= game->player->current_speed;
    }
    game->player->current_dir = UP;
  }  else if (direction == SDLK_DOWN) {
    printf("keyDown\n");
    if (game->player->y_pos < (game->sdl->screenSize.y - 40/*game->player->position.w*/) && game->map[(game->player->y_pos / 40) + 1][game->player->x_pos / 40] != 's') {
      game->player->y_pos += game->player->current_speed;
    }
    game->player->current_dir = DOWN;
  }  else if (direction == SDLK_LEFT) {
    printf("keyLeft\n");
    if (game->player->x_pos > 0 && game->map[game->player->y_pos / 40][(game->player->x_pos / 40) - 1] != 's') {
      game->player->x_pos -= game->player->current_speed;
    }
    game->player->current_dir = LEFT;
  }  else  if (direction == SDLK_RIGHT) {
    printf("keyRight\n");
    if (game->player->x_pos < (game->sdl->screenSize.x - 40/*game->player->position.h*/) && game->map[game->player->y_pos / 40][(game->player->x_pos / 40) + 1] != 's') {
      game->player->x_pos += game->player->current_speed;
    }
    game->player->current_dir = RIGHT;
  }
}
