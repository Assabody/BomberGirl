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
  int clip;
} bomb_t;

typedef struct sdl_s {
    SDL_Point screenSize;
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    SDL_Texture *bombTexture;
    SDL_Rect bomb_clips[4];
} sdl_t;

typedef struct          bomb_node_s
{
    bomb_t*             bomb;
    struct bomb_node_s*   next;
    struct bomb_node_s*   prev;
}                       bomb_node_t;

typedef struct          bombs_s
{
    struct bomb_node_s*   first;
    struct bomb_node_s*   last;
}                       bombs_t;

typedef struct game_s {
  struct sdl_s* sdl;
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
  
  SDL_Texture *bomb;

  bombs_t* bombs;
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

int gameDraw(game_t *);

void gameUpdate(game_t *game);

game_t *init();

game_t *initStructs();

void renderTexture(SDL_Texture *, game_t *, int, int, SDL_Rect *);

void	initGrass(game_t *);
int beginGame();

int menuWindow(game_t *);
void    showMenu(game_t *, char **, int, int);
void    showSelection(game_t *, int);
char    *showInputMenu(game_t *, const char *);
void showText(game_t *, const char *);
void  placeBomb(game_t *, int, int);
void removeBomb(game_t *, bomb_t *);

#endif
