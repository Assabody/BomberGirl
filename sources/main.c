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

    game->request.checksum = 0;
    game->request.magic = 0;
    game->server.started = 0;
    game->running = 1;
    game->player_key = -1;
    game->client_sock = -1;
    return game;
}


void gameDestroy(game_t *game) {
    puts("Cleaning everything...");
    if (game) {
        clearTextures(game->textures);
        clearSdl(game->sdl);
    }
}

int main() {
    game_t *game = init();
    
    srandom(time(0));
    if (game == NULL)
        return (EXIT_FAILURE);
    while (game->running) {
        menuWindow(game);
    }
    gameDestroy(game);
    free(game);
    return (EXIT_SUCCESS);
}
