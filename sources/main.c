#include "../includes/main.h"

game_t *init() {
    game_t *game = malloc(sizeof *game);
    if (!game) {
        return NULL;
    }
    game->sdl = initSdl();
    if (!game->sdl) {
        gameDestroy(game);
        return NULL;
    }
    game->textures = initTextures(game->sdl);
    if (!game->textures) {
        gameDestroy(game);
        return NULL;
    }
    game->bombs = initBombs();
    if (!game->bombs) {
        gameDestroy(game);
        return NULL;
    }
    game->player = initPlayer(1);
    if (!game->player) {
        gameDestroy(game);
        return NULL;
    }

    game->running = 1;
    game->client_sock = -1;
    return game;
}


void gameDestroy(game_t *game) {
    puts("Cleaning everything...");
    if (game) {
        clearTextures(game->textures);
        // TO DO: Fix Clear bombs (memory leak)
        clearBombs(game->bombs);
        clearPlayer(game->player);
        clearSdl(game->sdl);
        /*if (game->map != NULL) {
            clear_map(game);
        }*/
        TTF_Quit();
        SDL_Quit();
        free(game);
    }
}

int main() {
    game_t *game = init();

    /* Convert */
    //char *cell = malloc(sizeof(char) * 8);

    /*cell_t *map = mapInit();
    print_map(map);

    string_to_bytes(map[0].cell, cell);
    for(int i = 7; i >= 0; i--) {
        putchar(cell[i]);
    }

    printf("\nLa case %s.\n", is_cell_in_flame(map[0].cell) ? "est en flamme" : "n'est pas en flamme");
    printf("La case est de type ");
    switch (get_cell_type(map[0].cell)) {
        case MAP_WALL_BREAKABLE:
            printf("MAP_WALL_BREAKABLE\n");
            break;
        case MAP_WALL_UNBREAKABLE:
            printf("MAP_WALL_UNBREAKABLE\n");
            break;
        case MAP_GRASS:
            printf("MAP_GRASS\n");
            break;
    }
    printf("Il %s.\n", is_cell_bombed(map[0].cell) ? "y a une bombe" : "n'y a pas de bombe");
    if (cell_has_bonus(map[0].cell)) {
        switch (get_bonus(map[0].cell)) {
            case BOMB_NUMBER_BONUS:
                printf("Bonus de nombre de bombe\n");
                break;
            case BOMB_NUMBER_MALUS:
                printf("Malus de nombre de bombe\n");
                break;
            case RANGE_BONUS:
                printf("Bonus de portee de bombe\n");
                break;
            case RANGE_MALUS:
                printf("Malus de portee de bombe\n");
                break;
            case SPEED_BONUS:
                printf("Bonus de vitesse\n");
                break;
            case SPEED_MALUS:
                printf("Malus de vitesse\n");
                break;
        }
    }*/

    srandom(time(0));
    if (game == NULL)
        return (EXIT_FAILURE);
    while (game->running) {
        menuWindow(game);
    }
    gameDestroy(game);
    return (EXIT_SUCCESS);
}
