#include "../includes/main.h"

game_t *init() {
    game_t *game = malloc(sizeof *game);
    if (!game) {
        return NULL;
    }
    game->sdl = initSdl(680, 440);
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
    game->player = initPlayer();
    if (!game->player) {
        gameDestroy(game);
        return NULL;
    }

    game->running = 1;
    game->client_sock = -1;
    game->map = mapInit();
    return game;
}


void gameDestroy(game_t *game) {
    if (game) {
        clearTextures(game->textures);
        clearBombs(game->bombs);
        clearPlayer(game->player);
        // TO DO: Clear Map
        TTF_Quit();
        SDL_Quit();
        free(game);
    }
}

int main() {
    game_t *game = init();
    if (game == NULL)
        return (EXIT_FAILURE);
    while (game->running) {
        menuWindow(game);
    }
    gameDestroy(game);
    return (EXIT_SUCCESS);
}
