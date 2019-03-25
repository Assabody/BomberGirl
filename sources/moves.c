#include "../includes/main.h"

int can_go_to_cell(cell_t cell) {
    switch (get_cell_type(cell.cell)) {
        case MAP_GRASS:
            // if doesn't have bomb
            return 1;
        default:
            return 0;
    }
}

void player_coords_to_map_coords(int map_x, int map_y, int *player_x, int *player_y) {
    if (map_x <= 0) {
        *player_x = 0;
    }
    if (map_y <= 0) {
        *player_y = 0;
    }
    *player_x = map_x / 40;
    *player_y = map_y / 40;
}

void map_coords_to_player_coords(int player_x, int player_y, int *map_x, int *map_y) {
    if (player_x <= 0) {
        *map_x = 0;
    }
    if (player_x <= 0) {
        *map_x = 0;
    }
    *map_x = player_x * 40;
    *map_y = player_y * 40;
}

void movePlayer(game_t *game, SDL_Keycode direction) {
    int x;
    int y;
    game->request.magic = game->player.token;
    if (direction == SDLK_UP) {
        player_coords_to_map_coords(game->player.x_pos, game->player.y_pos - game->player.current_speed, &x, &y);
        game->request.x_pos = x;
        game->request.y_pos = y;
        // Server part
        /*if (can_go_to_cell(game->map[y][x])) {
            game->player.y_pos -= game->player.current_speed;
        }*/
        game->player.current_dir = UP;
    } else if (direction == SDLK_DOWN) {
        player_coords_to_map_coords(game->player.x_pos, game->player.y_pos + game->player.current_speed, &x, &y);
        game->request.x_pos = x;
        game->request.y_pos = y;
        // Server part
        /*if (can_go_to_cell(game->map[y][x])) {
            game->player.y_pos += game->player.current_speed;
        }*/
        game->player.current_dir = DOWN;
    } else if (direction == SDLK_LEFT) {
        player_coords_to_map_coords(game->player.x_pos - game->player.current_speed, game->player.y_pos, &x, &y);
        game->request.x_pos = x;
        game->request.y_pos = y;
        // Server part
        /*if (can_go_to_cell(game->map[y][x])) {
            game->player.x_pos -= game->player.current_speed;
        }*/
        game->player.current_dir = LEFT;
    } else if (direction == SDLK_RIGHT) {
        player_coords_to_map_coords(game->player.x_pos + game->player.current_speed, game->player.y_pos, &x, &y);
        game->request.x_pos = x;
        game->request.y_pos = y;
        // Server part
        /*if (can_go_to_cell(game->map[y][x])) {
            game->player.x_pos += game->player.current_speed;
        }*/
        game->player.current_dir = RIGHT;
    }
    game->request.dir = game->player.current_dir;
    game->request.command = 0;
    game->request.speed = game->player.current_speed;
    game->request.magic = (game->player.token + 1) * 16;
    printf("Player token is %d. magic is %d for request\n", game->player.token, game->request.magic);
}
