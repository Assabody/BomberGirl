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
    game->map = NULL; //mapInit();
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
        clear_map(game);
        TTF_Quit();
        SDL_Quit();
        free(game);
    }
}

int main() {
    game_t *game = init();
    print_map(game->map);

    srandom(time(0));
    if (game == NULL)
        return (EXIT_FAILURE);
    while (game->running) {
        menuWindow(game);
    }
    gameDestroy(game);
    return (EXIT_SUCCESS);
}
