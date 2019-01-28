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

  int texPosX = 0;
  int texPosY = 0;
  int i = 0;
  int j = 0;
  while (texPosY < 480) {
    while (texPosX < 640) {
      if (i % 2 == 1 && j % 2 == 1) {
	game->stonePosition.x = texPosX;
	SDL_RenderCopy(game->renderer, game->stone, NULL, &game->stonePosition);
      }
      else {
	game->grassPosition.x = texPosX;
	SDL_RenderCopy(game->renderer, game->grass, NULL, &game->grassPosition);
      }
      i++;
      texPosX += 40;
    }
    j++;
    i = 0;
    texPosY += 40;
    texPosX = 0;
    game->grassPosition.x = texPosX;
    game->stonePosition.x = texPosX;
    game->grassPosition.y = texPosY;
    game->stonePosition.y = texPosY;
  }

  /*  while (game->grassPosition.y < 480) {
    while (game->grassPosition.x < 640) {
      SDL_RenderCopy(game->renderer, game->grass, NULL, &game->grassPosition);
      game->grassPosition.x += 40;
      }
    game->grassPosition.x = 0;
    game->grassPosition.y += 40;
    }*/
} 

void    drawBombs(game_t *game)
{
    if (game->bomb != NULL) {
        SDL_RenderCopy(game->renderer, game->bombTexture, NULL, &game->bomb->position);
    }
}

void gameUpdate(game_t *game)
{
  if (game->bomb != NULL) {
      if (game->bomb->duration > 0) {
          game->bomb->duration--;
      } else {
          game->bomb = NULL;
      }
  }
}

void	gameDraw(game_t *game)
{
  SDL_RenderClear(game->renderer);
  gameUpdate(game);
  mapDraw(game);
  drawBombs(game);
  playerDraw(game);
  SDL_RenderPresent(game->renderer);
}
