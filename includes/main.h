/*
** ETNA PROJECT, 17/01/2019 by daurat_j
** Bomberman
** File description:
**      Header file
*/

#ifndef     _MAIN_H_
#define     _MAIN_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct  game_s
{
  
  int running;
  SDL_Point screenSize;
  SDL_Window *pWindow;
  SDL_Renderer *renderer;

  SDL_Texture* grass;
  SDL_Rect grassPosition;

  SDL_Texture* player;
  SDL_Rect playerPosition;

  SDL_Texture* bombe;
  SDL_Rect bombePosition;
}		game_t;

void    mapDraw(game_t *);
void    playerDraw(game_t *);
void    bombeDraw(game_t *);
void	movePlayer(game_t*, SDL_Keycode);
void	quitGame(game_t *);
void    initTextures(game_t *);
void	gameDestroy(game_t *);

int	checkEvents(game_t *);
int	gameDraw(game_t *);

game_t* init();
game_t*	initStructs();

#endif
