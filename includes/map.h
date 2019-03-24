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
#define MAP_BOMB 'b'

typedef struct cell_c {
    unsigned char cell;
    unsigned char bomb_timing;
} cell_t;

/**
 * Map.c
 */
cell_t **mapInit();

void print_map(cell_t **);

void clear_map(game_t *);

char *serialize_map(char **);

char **deserialize_map(char *);


#endif // _MAP_H_