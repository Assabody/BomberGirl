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

typedef struct  system_manager_s
{
    int running;
    SDL_Event events;
}   system_manager_t;

void inputManager(system_manager_t *manager);

#endif /* !_MAIN_H_ */
