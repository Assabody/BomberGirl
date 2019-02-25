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
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../network/network.h"

#define FPS 60
#define TICKS_PER_FRAME 1000 / FPS

typedef struct bomb_s {
  SDL_Rect position;
  int duration;
  SDL_Texture *bombTexture;
  SDL_Rect clips[4];
  int	useClips;
} bomb_t;

typedef struct window_s {
    SDL_Point screenSize;
    SDL_Window *pWindow;
    SDL_Renderer *renderer;
} window_t;

typedef struct game_s {
  SDL_Point screenSize;
  SDL_Window *pWindow;
  SDL_Renderer *renderer;
  char **map;
  
  SDL_Texture *grass;
  SDL_Rect grassPosition;
  
  SDL_Texture *stone;
  SDL_Rect stonePosition;
  
  SDL_Texture *wall;
  SDL_Rect wallPosition;
  
  SDL_Texture *player;
  SDL_Rect playerPosition;
  SDL_Rect oldPlayerPosition;
  int useClip;
  
  SDL_Texture *bombTexture;
  
  struct bomb_s* bomb;
  int speed;
  
  int running;
  Uint32 frameCount;

  int client_sock;
} game_t;

void mapDraw(game_t *);

char** mapInit();

//void wallDraw(game_t *);

void playerDraw(game_t *);

void bombeDraw(game_t *);
void drawBombs(game_t *);
void movePlayer(game_t *, SDL_Keycode);

void quitGame(game_t *);

void initTextures(game_t *);

void gameDestroy(game_t *);

void initBombe(game_t *, int);

void checkEvents(game_t *);

void gameDraw(game_t *);

void gameUpdate(game_t *game);

game_t *init();

game_t *initStructs();

void renderTexture(SDL_Texture *, game_t *, int, int, SDL_Rect *);

void	initGrass(game_t *);
int beginGame();

int showMenu(game_t *, TTF_Font *);

#endif
