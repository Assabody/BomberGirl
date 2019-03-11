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
    player->token = 0;
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

void printPlayerStruct(player_t *player) {
    printf("PlayerStruct\n  alive: %d\n  bombs: %d/%d\n  dir: %d\n  token: %d\n  speed: %d/%d\n  pos: X %d - Y %d\n  frags: %d\n\n", player->alive, player->bombs_left, player->bombs_capacity, player->current_dir, player->token, player->current_speed, player->max_speed, player->x_pos, player->y_pos, player->frags);
}