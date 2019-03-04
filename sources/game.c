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


int    gameDraw(game_t *game)
{
    if (game == NULL)
      return (EXIT_FAILURE);
    Uint32 frameStart;
    int frameTime;
    SDL_SetRenderDrawColor(game->sdl->renderer, 50, 50, 50, 255);
    while (game->running) {
      frameStart = SDL_GetTicks();
      SDL_RenderClear(game->sdl->renderer);
      gameUpdate(game);
      mapDraw(game);
      drawBombs(game);
      checkEvents(game);
      SDL_RenderPresent(game->sdl->renderer);
      frameTime = SDL_GetTicks() - frameStart;
      if (TICKS_PER_FRAME > frameTime)
        SDL_Delay(TICKS_PER_FRAME - frameTime);
      game->frameCount++;
    }
    return (EXIT_SUCCESS);
}