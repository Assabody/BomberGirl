/*
** ETNA PROJECT, 17/01/2019 by *
** Bomberman
** File description:
**      Header file
*/

#ifndef     _SDL_H_
#define     _SDL_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

typedef struct sdl_s {
    SDL_Window *window;
    SDL_Renderer *renderer;
    long int frameCount;
    TTF_Font *font;
} sdl_t;

typedef struct textures_s {
    SDL_Texture *menu;
    SDL_Texture *player;
    SDL_Texture *grass;
    SDL_Texture *stone;
    SDL_Texture *brick;
    SDL_Texture *bomb;
    SDL_Texture *flame;
    SDL_Texture *bomb_bonus;
    SDL_Texture *bomb_malus;
    SDL_Texture *range_bonus;
    SDL_Texture *range_malus;
    SDL_Rect bomb_clips[4];
    SDL_Rect player_clips[4];
} textures_t;

typedef struct menu_s {
    char *text;
    int enabled;
} menu_t;

sdl_t *initSdl();

void clearTextures(textures_t *);

void clearSdl(sdl_t *);

void renderTexture(SDL_Texture *, sdl_t *, int, int, SDL_Rect *);

#endif
