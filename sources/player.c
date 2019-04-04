#include "../includes/main.h"

void initPlayer(player_t *player, int player_position)
{
    player->alive = 0;
    player->bombs_capacity = 2;
    player->bombs_left = 2;
    player->current_dir = UP;
    player->token = player_position;
    player->current_speed = SPEED;
    player->max_speed = MAX_SPEED;
    player->frags = 0;
    player->life = PLAYER_LIFE;
    player->token = 0;
    player->bomb_radius = RADIUS;
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