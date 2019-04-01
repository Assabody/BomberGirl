/*
** ETNA PROJECT, 17/01/2019 by *
** Bomberman
** File description:
**      Header file
*/

#ifndef     _MAP_H_
#define     _MAP_H_

#define X_MAP_SIZE 15
#define Y_MAP_SIZE 13
#define MAP_WALL_BREAKABLE 3
#define MAP_WALL_UNBREAKABLE 1
#define MAP_GRASS 0

typedef struct cell_c {
    unsigned char cell;
    unsigned char duration;
} cell_t;

#endif //_MAP_H_
