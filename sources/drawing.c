#include "../includes/main.h"

void    playerDraw(game_t *game) {
  SDL_RenderCopy(game->renderer, game->player, NULL, &game->playerPosition);
}


void    bombeDraw(game_t *game) {
  game->bombePosition.x = game->oldPlayerPosition.x;
  game->bombePosition.y = game->oldPlayerPosition.y;    
  SDL_RenderCopy(game->renderer, game->bombe, NULL, &game->bombePosition);
}

void mapDraw(game_t *game)
{
  game->grassPosition.x = 0;
  game->grassPosition.y = 0;
  game->grassPosition.w = 40;
  game->grassPosition.h = 40;

  game->stonePosition.x = 0;
  game->stonePosition.y = 0;
  game->stonePosition.w = 40;
  game->stonePosition.h = 40;


  while (game->grassPosition.y < 480) {
    while (game->grassPosition.x < 640) {
      SDL_RenderCopy(game->renderer, game->grass, NULL, &game->grassPosition);
      game->grassPosition.x += 40;
      }
    game->grassPosition.x = 0;
    game->grassPosition.y += 40;
  }
}

void	gameDraw(game_t *game)
{
  SDL_RenderClear(game->renderer);
  mapDraw(game);
  if (game->bombeActive == 1)
    bombeDraw(game);
  if (game->bombeDuration >= 0)
    game->bombeDuration--;
  if (game->bombeDuration == 0)
    SDL_DestroyTexture(game->bombe);
  playerDraw(game);
  SDL_RenderPresent(game->renderer);
}
