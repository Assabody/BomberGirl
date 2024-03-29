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
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <signal.h>
#include "../includes/sdl.h"
#include "../includes/map.h"
#include "../includes/player.h"
#include "../network/network.h"
#include "../network/request.h"
#include "../network/server.h"

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
#define RADIUS 3

// bonus
#define RANGE_BONUS 0 // 000
#define RANGE_MALUS 4 // 001
#define BOMB_NUMBER_BONUS 2 // 010
#define BOMB_NUMBER_MALUS 6 // 011

typedef struct server_s
{
    pthread_t server_thread;
    int port;
    int started;
    int waiting_lobby;
    int players_connected;
} server_t;

typedef struct game_s {
  sdl_t *sdl;
  player_t player[MAX_PLAYERS];
  textures_t *textures;
  server_t server;

  cell_t map[Y_MAP_SIZE][X_MAP_SIZE];
  t_client_request request;
  
  int running;
  int player_key;
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
void mapInit(game_infos_t *);

void print_map(game_t *);

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
 * Menu.c
 */
int menuWindow(game_t *);

void showMenu(game_t *, menu_t *, int, int);

void showSelection(game_t *, int);

char *showInputTextMenu(game_t *, const char *);

char *showInputNumberMenu(game_t *, const char *);

void showPromptMessage(game_t *, const char *, SDL_Rect, SDL_Color);

int hostGame(game_t *);

int waitingLobby(game_t *, int);

void ask_for_ip(SDL_Renderer *, TTF_Font *, char *);

void ask_for_port(SDL_Renderer *, TTF_Font *, char *);


/**
 * Drawing.c
 */
void drawBombs(game_t *, SDL_Rect);

void drawPlayer(game_t *game);

void drawMap(game_t *);

int drawGame(game_t *);

void disp_text(SDL_Renderer *, char *, TTF_Font *, int, int);

void drawHUD(game_t *);

/**
 * Player.c
 */
void initPlayer(player_t *, int);

/**
 * Cell.c
 */
void show_bits(int);
void toggle_byte(unsigned char *, int);
void clear_byte(unsigned char *, int);
int test_byte(unsigned char, int);
int is_grass(unsigned char);
int is_breakable(unsigned char);
int is_unbreakable(unsigned char);
int is_bonus(unsigned char);
int is_bomb(unsigned char);
int is_flame(unsigned char);
void set_bonus(unsigned char *, int);
void set_bomb(unsigned char *, int);
void set_flame(unsigned char *, int);
void set_grass(unsigned char *);
void set_breakable(unsigned char *);
void set_unbreakable(unsigned char *);
// TO MOVE
int get_bonus(unsigned char);
void remove_bonus(unsigned char *);
int can_pose_bomb(unsigned char);
void explode_cell(cell_t *);

/**
 * Moves.c
 */
int can_go_to_cell(cell_t);

void map_coords_to_player_coords(int, int, int *, int *);

void player_coords_to_map_coords(int, int, int *, int *);

/**
 * Client.c
 */
int getServerInfo(int, game_t *);

int initClient(char *, char *, game_t *);

/**
 * Server.c
 */
void startServer(game_t *, int *);

void stopServer(game_t *);

void *server(void *arg);

/**
 * Request.c
 */
int send_request(game_t *game);

#endif
