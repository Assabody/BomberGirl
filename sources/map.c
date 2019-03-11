#include "../includes/main.h"

char **mapInit()
{
    int x = 0;
    int y = 0;
    char **map;

    map = malloc(sizeof(char *) * (Y_MAP_SIZE));
    while (y < Y_MAP_SIZE) {
        map[y] = malloc(sizeof(char) * (X_MAP_SIZE));
        while (x < X_MAP_SIZE) {
            if (x == X_MAP_SIZE - 1 || y == Y_MAP_SIZE - 1 || x == 0 || y == 0) {
                // borders
                map[y][x] = MAP_WALL_UNBREAKABLE;
            } else if (x % 2 == 0 && y % 2 == 0) {
                // every two lines and rows
                map[y][x] = MAP_WALL_UNBREAKABLE;
            } else if (
                    (x >= 1 && x <= 2 && y >= 1 && y <= 2) ||
                    (x >= X_MAP_SIZE - 3 && x <= X_MAP_SIZE - 2 && y >= Y_MAP_SIZE - 3 && y <= Y_MAP_SIZE - 2) ||
                    (x >= 1 && x <= 2 && y >= Y_MAP_SIZE - 3 && y <= Y_MAP_SIZE - 2) ||
                    (x >= X_MAP_SIZE - 3 && x <= X_MAP_SIZE - 2 && y >= 1 && y <= 2)
                    ) {
                // Put grass where the players spawn
                map[y][x] = MAP_GRASS;
            } else {
                map[y][x] = MAP_WALL_BREAKABLE;
            }
            x++;
        }
        x = 0;
        y++;
    }
    return map;
}

void print_map(char **map)
{
    if (map != NULL) {
        for (int y = 0; y < Y_MAP_SIZE; y++) {
            for (int x = 0; x < X_MAP_SIZE; x++) {
                putchar(map[y][x]);
                putchar(' ');
            }
            putchar('\n');
        }
    }
}

void clear_map(game_t *game)
{
    for (int y = 0; y < Y_MAP_SIZE; y++) {
        free(game->map[y]);
    }
    free(game->map);
}

char *serialize_map(char **map)
{
    int i = 0;
    char *serialized_map = malloc(sizeof(* serialized_map) * (X_MAP_SIZE * Y_MAP_SIZE));
    if (map != NULL) {
        for (int y = 0; y < Y_MAP_SIZE; y++) {
            for (int x = 0; x < X_MAP_SIZE; x++) {
                serialized_map[i++] = map[y][x];
            }
        }
    }
    return serialized_map;
}

char **deserialize_map(char *serialized_map)
{
    char **map;
    int i = 0;

    map = malloc(sizeof(char *) * Y_MAP_SIZE);
    for (int y = 0 ; y < Y_MAP_SIZE; y++) {
        map[y] = malloc(sizeof(char) * X_MAP_SIZE);
        for (int x = 0 ; x < X_MAP_SIZE; x++) {
            map[y][x] = serialized_map[i++];
        }
    }
    return map;
}