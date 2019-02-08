#include "../includes/main.h"
void    playerDraw(game_t *game) {
  SDL_Surface *playerSurface = IMG_Load("./assets/images/sprite_player_2.png");
  SDL_Texture* pTexture = SDL_CreateTextureFromSurface(game->renderer,playerSurface);
  int iW = 40, iH = 60;
  SDL_Rect clips[4];
  if ( pTexture )
    {
      SDL_Rect dest = { 640/2 - playerSurface->w/2,480/2 - playerSurface->h/2, playerSurface->w, playerSurface->h};
      SDL_BlitSurface(playerSurface,NULL,SDL_GetWindowSurface(game->pWindow),&dest);
      for (int i = 0; i < 4; ++i){
	clips[i].x = i / 2 * iW;
	clips[i].y = i % 2 * iH;
	clips[i].w = iW;
	clips[i].h = iH;
      }
      renderTexture(pTexture, game, game->playerPosition.x, (game->playerPosition.y - 20), &clips[game->useClip]);
    }
  else
    {
      fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
    }

  SDL_FreeSurface(playerSurface);
}

void renderTexture(SDL_Texture *tex, game_t *game, int x, int y, SDL_Rect *clip)
{
  SDL_Rect dst;
  dst.x = x;
  dst.y = y;
  if (clip != NULL){
    dst.w = clip->w;
    dst.h = clip->h;
  }
  else {
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
  }
  SDL_RenderCopy(game->renderer, tex, clip, &dst);
}

void    bombeDraw(game_t *game) {
  SDL_RenderCopy(game->renderer, game->bombTexture, NULL, &game->bomb->position);
}

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
  return map;
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
  int x = 0;
  int y = 0;

  while (game->map[y])
    {
      while (game->map[y][x])
	{
	  if (game->map[y][x] == 'g')
	    {
	      game->grassPosition.x = texPosX;
	      SDL_RenderCopy(game->renderer, game->grass, NULL, &game->grassPosition);
	    }
	  else
	    {
	      game->stonePosition.x = texPosX;
	      SDL_RenderCopy(game->renderer, game->stone, NULL, &game->stonePosition);
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
}
