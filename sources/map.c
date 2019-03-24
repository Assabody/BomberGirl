#include "../includes/main.h"
#include "../includes/map.h"
#include "../includes/cell.h"

cell_t *mapInit()
{
    int i;
    cell_t *map;

    map = malloc(sizeof(*map) * Y_MAP_SIZE * X_MAP_SIZE);

    for (i = 0; i < X_MAP_SIZE * Y_MAP_SIZE; i++) {
        map[i].cell = 0;
        map[i].cell = unbreakable_wall_cell(map[i].cell);
        map[i].bomb_timing = 0;
    }
    return map;
}

void print_map(cell_t *map)
{
    if (map != NULL) {
        for (int y = 0; y < Y_MAP_SIZE * X_MAP_SIZE; y++) {
            switch (get_cell_type(map[y].cell)) {
                case MAP_WALL_UNBREAKABLE:
                    printf("u");
                    break;
                case MAP_WALL_BREAKABLE:
                    printf("b");
                    break;
                case MAP_GRASS:
                    printf("g");
                    break;
                default:
                    printf("other: %d\n", get_cell_type(map[y].cell));

            }
            putchar(' ');
            if (y % Y_MAP_SIZE == 0) {
                putchar('\n');
            }
        }
    }
}

void clear_map(game_t *game)
{
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