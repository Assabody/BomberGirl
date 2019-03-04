#include "../includes/main.h"

char** mapInit()
{
  int x = 0;
  int y = 0;
  char **map;
  
  map = malloc(sizeof(char*) * 12);
  while (y < 11) {
    map[y] = malloc(sizeof(char) * 18);
    while (x < 17) {
      if (x == 16 || y == 10 || x == 0 || y == 0)
	map[y][x] = 's'; //Wall
      else if (x % 2 == 1 && y % 2 == 1)
	map[y][x] = 's';
      else 
	map[y][x] = 'g';
      x++;
    }
    map[y][x] = '\0';
    x = 0;
    y++;
  }
  map[y] = NULL;
  return map;
}

void	initGrass(game_t *game)
{
  game->grassPosition.x = 0;
  game->grassPosition.y = 0;
  game->grassPosition.w = 40;
  game->grassPosition.h = 40;
  game->stonePosition.x = 0;
  game->stonePosition.y = 0;
  game->stonePosition.w = 40;
  game->stonePosition.h = 40;
}

void mapDraw(game_t *game)
{
  int texPosX = 0;
  int texPosY = 0;
  int x = 0;
  int y = 0;
  
  initGrass(game);
  while (game->map[y])
    {
      while (game->map[y][x])
	{
	  if (game->map[y][x] == 'g')
	    {
	      game->grassPosition.x = texPosX;
	      SDL_RenderCopy(game->sdl->renderer, game->grass, NULL, &game->grassPosition);
	    }
	  else
	    {
	      game->stonePosition.x = texPosX;
	      SDL_RenderCopy(game->sdl->renderer, game->stone, NULL, &game->stonePosition);
	    }
	  x++;
	  texPosX += 40;
	}
      x = 0;
      y++;
      texPosY += 40;
      texPosX = 0;
      game->grassPosition.x = texPosX;
      game->stonePosition.x = texPosX;
      game->grassPosition.y = texPosY;
      game->stonePosition.y = texPosY;
    }
}

void    drawBombs(game_t *game)
{
    bomb_node_t* bomb_node = game->bombs->first;
    while (bomb_node != NULL) {
        if (bomb_node->bomb->duration <= 0) {
            removeBomb(game, bomb_node->bomb);
            break;
        }
        renderTexture(game->bomb, game, bomb_node->bomb->position.x, bomb_node->bomb->position.y, &game->sdl->bomb_clips[bomb_node->bomb->clip]);
        //renderTexture(game->sdl->bombTexture, game, bomb_node->bomb->position.x, bomb_node->bomb->position.y, &game->sdl->bomb_clips[bomb_node->bomb->clip]);
        bomb_node = bomb_node->next;
    }
}