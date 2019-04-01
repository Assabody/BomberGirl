#include "../includes/main.h"

void initPlayer(player_t *player, int player_position)
{
    player->alive = 0;
    player->bombs_capacity = 1;
    player->bombs_left = 1;
    player->current_dir = UP;
    player->token = player_position;
    player->current_speed = SPEED;
    player->max_speed = MAX_SPEED;
    player->frags = 0;
    player->life = 30;
    printf("%i\n\n", player->life);
    switch (player_position) {
        case 1:
            map_coords_to_player_coords(1, 1, &player->x_pos, &player->y_pos);
            break;
        case 2:
            map_coords_to_player_coords(X_MAP_SIZE - 2, 1, &player->x_pos, &player->y_pos);
            break;
        case 3:
            map_coords_to_player_coords(1, Y_MAP_SIZE - 2, &player->x_pos, &player->y_pos);
            break;
        case 4:
            map_coords_to_player_coords(X_MAP_SIZE - 2, Y_MAP_SIZE - 2, &player->x_pos, &player->y_pos);
            break;
    }
}

void printPlayerStruct(player_t *player) {
    printf("PlayerStruct\n  alive: %d\n  bombs: %d/%d\n  dir: %d\n  token: %d\n  speed: %d/%d\n  pos: X %d - Y %d\n  frags: %d\n\n", player->alive, player->bombs_left, player->bombs_capacity, player->current_dir, player->token, player->current_speed, player->max_speed, player->x_pos, player->y_pos, player->frags);
}
