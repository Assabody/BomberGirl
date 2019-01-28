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
    while (texPosX < 680) {
      if ((i % 2 == 1 && j % 2 == 1) && (texPosX < 640 && texPosY < 400)) {
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
  wallDraw(game);
}


void	wallDraw(game_t *game)
{
  game->wallPosition.x = 0;
  game->wallPosition.y = 0;
  game->wallPosition.w = 40;
  game->wallPosition.h = 40;
  
  int texPosX = 0;
  int texPosY = 0;
  while (texPosY < 480) {
    while (texPosX < 680) {
      // DRAW LEFT - RIGHT BORDER
      SDL_RenderCopy(game->renderer, game->wall, NULL, &game->wallPosition);
      game->wallPosition.x = 640;
      SDL_RenderCopy(game->renderer, game->wall, NULL, &game->wallPosition);

      // DRAW TOP - BOTTOM BORDER
      if (game->wallPosition.x == 640) {
	game->wallPosition.x = 0;
	while (game->wallPosition.x <= 600) {
	  game->wallPosition.x += 40;
	  game->wallPosition.y = 0;
	  SDL_RenderCopy(game->renderer, game->wall, NULL, &game->wallPosition);
	  game->wallPosition.y = 400;
	  SDL_RenderCopy(game->renderer, game->wall, NULL, &game->wallPosition);
	}
      }
      texPosX += 40;
    }
    texPosY += 40;
    texPosX = 0;
    game->wallPosition.x = texPosX;
    game->wallPosition.y = texPosY;
  }
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
