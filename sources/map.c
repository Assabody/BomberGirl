#include "../includes/main.h"

char **mapInit() {
    int x = 0;
    int y = 0;
    char **map;

    map = malloc(sizeof(char *) * (Y_MAP_SIZE));
    while (y <=Y_MAP_SIZE) {
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
        map[y][x] = '\0';
        x = 0;
        y++;
    }
    map[y] = NULL;
    return map;
}

void print_map(char ** map) {
    for (int y = 0; y < Y_MAP_SIZE; y++) {
        for (int x = 0; x < X_MAP_SIZE; x++) {
            putchar(map[y][x]);
            putchar(' ');
        }
        putchar('\n');
    }
}