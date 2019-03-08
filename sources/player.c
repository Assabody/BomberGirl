#include "../includes/main.h"

player_t *initPlayer(void)
{
    player_t *player = malloc(sizeof *player);
    if (!player) {
        return NULL;
    }

    player->alive = 1;
    player->bombs_capacity = 1;
    player->bombs_left = 1;
    player->current_dir = UP;
    player->token = randomNumber(0, 65536);
    player->current_speed = SPEED;
    player->max_speed = MAX_SPEED;
    player->frags = 0;
    player->x_pos = 80;
    player->y_pos = 80;
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