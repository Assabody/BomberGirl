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
int my_pow(int nb, int pow)
{
    int p;
    int result;

    p = 1;
    result = 1;
    if (pow < 0)
        return (0);
    if (pow == 0)
        return (1);
    while (p <= pow)
    {
        result = result * nb;
        p = p + 1;
    }
    return (result);
}

void showbits(int x)
{
    for (int i = 8 - 1; i >= 0; i--)
    {
        (x & (1 << i)) ? putchar('1') : putchar('0');
    }
    printf("\n");
}

int main() {
    cell_t cell;
    cell.cell  = 7; // flame + breakable
    //printf("%d\n", cell.cell);
    showbits(cell.cell);
    putchar('\n');
    clear_byte(&cell.cell, 1);
    //printf("%d\n", cell.cell);
    showbits(cell.cell);
    putchar('\n');
    exit(0);
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
