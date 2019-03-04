#include "../includes/main.h"

void gameUpdate(game_t *game)
{
    int bombs_count = 0;
    int count = 0;
    bomb_node_t* bomb_node = game->bombs->first;
    while (bomb_node != NULL) {
        count++;
        if (bomb_node->bomb != NULL) {
            bombs_count++;
            if (bomb_node->bomb->duration > 0) {
                if (bomb_node->bomb->duration > 80 && bomb_node->bomb->duration < 110) {
                    bomb_node->bomb->clip = 2;
                }
                if (bomb_node->bomb->duration > 15 && bomb_node->bomb->duration < 50) {
                    bomb_node->bomb->clip = 1;
                }
                if (bomb_node->bomb->duration > 0 && bomb_node->bomb->duration < 15) {
                    bomb_node->bomb->clip = 3;
                }
                bomb_node->bomb->duration--;
            } else {
                bomb_node->bomb = NULL;
            }
        }
        bomb_node = bomb_node->next;
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