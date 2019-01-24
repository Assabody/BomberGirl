#include "../includes/main.h"

void    playerDraw(game_t *game) {
  SDL_RenderCopy(game->renderer, game->player, NULL, &game->playerPosition);
}


void    bombeDraw(game_t *game) {
  SDL_RenderCopy(game->renderer, game->bombe, NULL, &game->bombePosition);
}

void mapDraw(game_t *game)
{
  game->grassPosition.x = 0;
  game->grassPosition.y = 0;
  game->grassPosition.w = 40;
  game->grassPosition.h = 40;

  while (game->grassPosition.y < 480) {
    while (game->grassPosition.x < 640) {
      SDL_RenderCopy(game->renderer, game->grass, NULL, &game->grassPosition);
      game->grassPosition.x += 40;
    }
    game->grassPosition.x = 0;
    game->grassPosition.y += 40;
  }
}

int	gameDraw(game_t *game)
{
  int	quit = 0;
  SDL_SetRenderDrawColor(game->renderer, 50, 50, 50, 255);
  SDL_RenderClear(game->renderer);

  mapDraw(game);
  playerDraw(game);
  quit = checkEvents(game);
  
  SDL_RenderPresent(game->renderer);
  return (quit);
}
