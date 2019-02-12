#include "../includes/main.h"

void    bombeDraw(game_t *game) {
  int iW = 40, iH = 40;
  bomb_t *bomb;
  SDL_Surface *bombeSurface = IMG_Load("./assets/images/bombeSprite.png");

  bomb = malloc(sizeof(bomb_t));
  bomb->bombTexture = SDL_CreateTextureFromSurface(game->renderer,bombeSurface);
  bomb->position.x = game->playerPosition.x;
  bomb->position.y = game->playerPosition.y;
  bomb->duration = 2 * FPS;
  bomb->position.w = iW;
  bomb->position.h = iH;
  bomb->useClips = 0;
  game->bomb = bomb;
  if ( game->bomb->bombTexture )
    {
      SDL_Rect dest = { 640/2 - bombeSurface->w/2,480/2 - bombeSurface->h/2, bombeSurface->w, bombeSurface->h};
      SDL_BlitSurface(bombeSurface,NULL,SDL_GetWindowSurface(game->pWindow),&dest);
      for (int i = 0; i < 4; ++i){
	game->bomb->clips[i].x = i / 2 * iW;
	game->bomb->clips[i].y = i % 2 * iH;
	game->bomb->clips[i].w = iW;
	game->bomb->clips[i].h = iH;
      }
      renderTexture(game->bomb->bombTexture, game, game->bomb->position.x, game->bomb->position.y, &game->bomb->clips[game->bomb->useClips]);
    }
  else
    {
      fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
    }

  SDL_FreeSurface(bombeSurface);
}

void    drawBombs(game_t *game)
{
  if (game->bomb != NULL) {
    renderTexture(game->bomb->bombTexture, game, game->bomb->position.x, game->bomb->position.y, &game->bomb->clips[game->bomb->useClips]);
  }
}
