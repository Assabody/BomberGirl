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
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../network/network.h"
#include "../network/request.h"

#define FPS 60
#define TICKS_PER_FRAME 1000 / FPS

// constants for players
#define SPEED 40
#define MAX_SPEED 10

#define SCREEN_SIZE_X 600
#define SCREEN_SIZE_Y 520

// same as the player clips
#define UP 2
#define DOWN 0
#define RIGHT 1
#define LEFT 3

// bombs
#define DAMAGES 10
#define PLAYER_LIFE 30
#define WALL_LIFE 10
#define RADIUS 40

typedef struct bomb_s {
  int x;
  int y;
  int duration;
  int damages;
  int clip;
} bomb_t;

typedef struct breakablewall_s {
  int	life;
}	       breakablewall_t;

typedef struct sdl_s {
  SDL_Window *window;
  SDL_Renderer *renderer;
  long int frameCount;
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

typedef struct player_s
{
  int token;
  int alive;
  int x_pos;
  int y_pos;
  int current_dir;
  int current_speed;
  int max_speed;
  int bombs_left;
  int bombs_capacity;
  int frags;
  int life;
} player_t;

typedef struct textures_s {
  SDL_Texture *menu;
  SDL_Texture *player;
  SDL_Texture *grass;
  SDL_Texture *stone;
  SDL_Texture *brick;
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

/*
** Bit 0 : Indique si la case est en flammes (1) ou non (0)
** Bits [1..2] : Indique le type de terrain ( 00 : Terrain vide, 10 : Brique indestructible, 11 : Brique destructible). Note : Combinaison 01 inutilisée.
** Bit 3 : Présence d’une bombe (0 : Pas de bombe, 1 : Bombe)
** Bit 4 : Présence d’un bonus / malus (0 : Pas de bonus / malus, 1 : Bonus / malus présent)
** Bits [5..7] : Type de bonus / malus.
**
** Pour l’exemple, liste des bonus / malus
** 000 : Bonus portée bombes
** 001 : Malus portée bombes
** 010 : Bonus nombre bombes
** 011 : Malus nombre bombes
** 100 : Bonus vitesse
** 101 : Malus vitesse
** 110 : Rien
** 111 : Rien
*/

/**
 * Map.c
 */
char **mapInit();

void print_map(char **);

void clear_map(game_t *);

char *serialize_map(char **);

char **deserialize_map(char *);


void movePlayer(game_t *, SDL_Keycode);

void quitGame(game_t *);

textures_t* initTextures(sdl_t *);

void gameDestroy(game_t *);

game_t *init(void);

/**
 * Events.c
 */
void checkEvents(game_t *);


/**
 * Sdl.c
 */
sdl_t *initSdl();

void clearTextures(textures_t *);

void clearSdl(sdl_t *);

void renderTexture(SDL_Texture *, game_t *, int, int, SDL_Rect *);

/**
 * Menu.c
 */
int menuWindow(game_t *);

void showMenu(game_t *, char **, int, int);

void showSelection(game_t *, int);

char *showInputMenu(game_t *, const char *);

void showText(game_t *, const char *);

int getClientToken(int);



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
bombs_t *initBombs(void);

void clearBombs(bombs_t *);

void placeBomb(game_t *, int, int);

void removeBomb(game_t *, bomb_t *);

void removeBombNode(bombs_t *, bomb_node_t *);

void bombExplosion(bomb_t *, game_t *);

void updateBombs(game_t *);

void bombCheckObjectRadius(game_t *, bomb_t *);

void checkPlayerDamagesFromBombs(game_t *, bomb_t *);

/**
 * Player.c
 */
player_t *initPlayer(int);

void clearPlayer(player_t *);

void printPlayerStruct(player_t *);

int initClient(char *, char *, game_t *);


/**
 * Game.c
 */
int fetchDataFromServer(game_t *game);


#endif
