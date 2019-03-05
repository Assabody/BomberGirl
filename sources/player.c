#include "../includes/main.h"

player_t *initPlayer(void)
{
    player_t *player = malloc(sizeof *player);
    if (!player) {
        return NULL;
    }

    player->clip = 0;
    player->speed = 1;
    player->position.x = 80;
    player->position.y = 80;
    player->position.w = 40;
    player->position.h = 40;

    return player;
}

void clearPlayer(player_t *player)
{
    puts("Clearing Player");
    if (player) {
        free(player);
    }
    player = NULL;
    puts("Player cleared");
}