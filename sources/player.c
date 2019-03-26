#include "../includes/main.h"

void initPlayer(player_t *player, int player_position)
{
    player->alive = 1;
    player->bombs_capacity = 1;
    player->bombs_left = 1;
    player->current_dir = UP;
    player->token = player_position;
    player->current_speed = SPEED;
    player->max_speed = MAX_SPEED;
    player->frags = 0;
    player->life = PLAYER_LIFE;
    printf("X_POS: %i\n" , player->x_pos);
    printf("Y_POS: %i\n" , player->y_pos);
    printf("PLAYER_LIFE: %i\n", player->life);
    switch (player_position) {
        case 1:
            player->x_pos = 40;
            player->y_pos = 40;
            break;
        case 2:
            player->x_pos = X_MAP_SIZE - 40;
            player->y_pos = 40;
            break;
        case 3:
            player->x_pos = 40;
            player->y_pos = Y_MAP_SIZE - 40;
            break;
        case 4:
            player->x_pos = X_MAP_SIZE - 40;
            player->y_pos = Y_MAP_SIZE - 40;
            break;
    }
}

void printPlayerStruct(player_t *player) {
  printf("PlayerStruct\n  alive: %d\n  bombs: %d/%d\n  dir: %d\n  token: %d\n  speed: %d/%d\n  pos: X %d - Y %d\n  frags: %d\n\n", player->alive, player->bombs_left, player->bombs_capacity, player->current_dir, player->token, player->current_speed, player->max_speed, player->x_pos, player->y_pos, player->frags);
}

/*
char *serializePlayer(player_t *player)
{
    char *buffer = malloc(sizeof(char) * (8 * 10);
    strcpy(buffer, serialize_int(player->token));
    buffer
    buffer[81] =
}*/
