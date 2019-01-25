#include "../includes/main.h"

void    playerDraw(game_t *game) {
  SDL_RenderCopy(game->renderer, game->player, NULL, &game->playerPosition);
}


void    bombeDraw(game_t *game) {
  SDL_RenderCopy(game->renderer, game->bombTexture, NULL, &game->bomb->position);
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

void    drawBombs(game_t *game)
{
    if (game->bomb != NULL) {
        SDL_RenderCopy(game->renderer, game->bombTexture, NULL, &game->bomb->position);
        printf("printing bomb\n");
    } else {
        printf("no bombs\n");
    }
}

void	gameDraw(game_t *game)
{
  SDL_RenderClear(game->renderer);
  mapDraw(game);
  if (game->bomb != NULL && game->bomb->duration > 0) {
    game->bomb->duration--;
  } else {
    game->bomb = NULL;
  }
  drawBombs(game);
  playerDraw(game);
  SDL_RenderPresent(game->renderer);
}
