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
    int x;
    int y;
    int duration;
    int clip;
} bomb_t;

typedef struct sdl_s {
    SDL_Point screenSize;
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
} sdl_t;

typedef struct bomb_node_s {
    bomb_t *bomb;
    struct bomb_node_s *next;
    struct bomb_node_s *prev;
} bomb_node_t;

typedef struct bombs_s {
    struct bomb_node_s *first;
    struct bomb_node_s *last;
} bombs_t;

typedef struct player_s {
    SDL_Rect position;
    SDL_Rect oldPosition;
    int speed;
    int clip;

} player_t;

typedef struct textures_s {
    SDL_Texture *player;
    SDL_Texture *grass;
    SDL_Texture *stone;
    SDL_Texture *bomb;
    SDL_Rect bomb_clips[4];
    SDL_Rect player_clips[4];
} textures_t;

typedef struct game_s {
    sdl_t *sdl;
    bombs_t *bombs;
    player_t *player;
    textures_t *textures;

    char **map;

    int running;
    int client_sock;
} game_t;

char **mapInit();

void movePlayer(game_t *, SDL_Keycode);

void quitGame(game_t *);

textures_t* initTextures(sdl_t *);

void gameDestroy(game_t *);

game_t *init();

game_t *initStructs();

/**
 * Events.c
 */
void checkEvents(game_t *);


/**
 * Sdl.c
 */
void renderTexture(SDL_Texture *, game_t *, int, int, SDL_Rect *);
void destroyTextures(textures_t *);

/**
 * Menu.c
 */
int menuWindow(game_t *);

void showMenu(game_t *, char **, int, int);

void showSelection(game_t *, int);

char *showInputMenu(game_t *, const char *);

void showText(game_t *, const char *);


/**
 * Drawing.c
 */
void drawBombs(game_t *);

void drawPlayer(game_t *game);

void drawMap(game_t *);

int drawGame(game_t *);


/**
 * Bomb.c
 */
void placeBomb(game_t *, int, int);

bombs_t *initBombs(void);

void removeBomb(game_t *, bomb_t *);

void removeBombNode(bombs_t *, bomb_node_t *);

void updateBombs(game_t *);

#endif
