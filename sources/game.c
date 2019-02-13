#include "../includes/main.h"

void gameUpdate(game_t *game)
{
  if (game->bomb != NULL) {
    if (game->bomb->duration > 0) {
      if (game->bomb->duration > 80 && game->bomb->duration < 110) {
	game->bomb->useClips = 2;
      }
      if (game->bomb->duration > 15 && game->bomb->duration < 50) {
	game->bomb->useClips = 1;
      }
      if (game->bomb->duration > 0 && game->bomb->duration < 15) {
	game->bomb->useClips = 3;
      }

      game->bomb->duration--;
    } else {
      game->bomb = NULL;
    }
  }
}


void    gameDraw(game_t *game)
{
  SDL_RenderClear(game->renderer);
  gameUpdate(game);
  mapDraw(game);
  drawBombs(game);
}

