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

#define FPS 60
#define TICKS_PER_FRAME 1000 / FPS

typedef struct bomb_s {
    SDL_Rect position;
    int duration;
} bomb_t;

typedef struct game_s {
    SDL_Point screenSize;
    SDL_Window *pWindow;
    SDL_Renderer *renderer;

    SDL_Texture *grass;
    SDL_Rect grassPosition;

    SDL_Texture *stone;
    SDL_Rect stonePosition;

    SDL_Texture *player;
    SDL_Rect playerPosition;
    SDL_Rect oldPlayerPosition;

    SDL_Texture *bombTexture;

    struct bomb_s* bomb;
    int speed;

    int running;
    Uint32 frameCount;
} game_t;

void mapDraw(game_t *);

void playerDraw(game_t *);

void bombeDraw(game_t *);

void movePlayer(game_t *, SDL_Keycode);

void quitGame(game_t *);

void initTextures(game_t *);

void gameDestroy(game_t *);

void initBombe(game_t *, int);

void checkEvents(game_t *);

void gameDraw(game_t *);

game_t *init();

game_t *initStructs();

#endif
