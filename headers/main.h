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

typedef struct  system_manager_s
{
    int running;
    SDL_Event events;
}   system_manager_t;

//Texture
typedef struct  texture_container_s
{
  SDL_Texture* grass;
  SDL_Rect grassPosition;
}   texture_container_t;

typedef struct  game_s
{
  SDL_Renderer *renderer;
}   game_t;

void inputManager(system_manager_t *manager);
void mapDraw(game_t *game, texture_container_t *texture_container);
int init();

#endif /* !_MAIN_H_ */
