#include "../includes/main.h"

char **mapInit() {
    int x = 0;
    int y = 0;
    char **map;

    map = malloc(sizeof(char *) * 12);
    while (y < 11) {
        map[y] = malloc(sizeof(char) * 18);
        while (x < 17) {
            if (x == 16 || y == 10 || x == 0 || y == 0)
                map[y][x] = 's'; //Wall
            else if (x % 2 == 1 && y % 2 == 1)
                map[y][x] = 's';
            else
                map[y][x] = 'g';
            x++;
        }
        map[y][x] = '\0';
        x = 0;
        y++;
    }
    map[y] = NULL;
    return map;
}