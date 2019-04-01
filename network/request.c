#include "request.h"
#include "../includes/main.h"

int send_bomb_exploded(int socket, int x, int y) {
    int x_map;
    int y_map;
    t_client_request request;
    player_coords_to_map_coords(x, y, &x_map, &y_map);
    request.speed = 2 * FPS;
    request.command = 0;
    request.x_pos = x_map;
    request.y_pos = y_map;
    return send(socket, &request, sizeof(request), MSG_NOSIGNAL);
}

int send_request(game_t *game) {
    game->request.magic = (game->player_key + 1) * 16;
    game->request.checksum = game->request.dir + game->request.speed + game->request.command + game->request.x_pos + game->request.y_pos + game->request.magic;

    if (send(game->client_sock, &game->request, sizeof(game->request), MSG_NOSIGNAL)) {
        game->request.magic = 0;
        game->request.command = 0;
        game->request.checksum = 0;
        game->request.dir = UP;
        game->request.speed = game->player[game->player_key].current_speed;
        return 1;
    }
    return 0;
}

int verify_request(t_client_request request) {
    if (request.checksum == request.magic + request.y_pos + request.x_pos + request.command + request.speed + request.dir) {
        return 1;
    } else if (!request.command && request.speed == 2 * FPS) {
        return 1;
    }
    return 0;
}

void string_to_bytes(char n, char *str)
{
    for (int i = 7; i >= 0; i--) {
        if (((n >> i) & 0x01) == 0) {
            str[i] = '0';
        } else {
            str[i] = '1';
        }
    }
}

int bytes_to_int(char n)
{
    int result = 0;
    for (int i = 0; i <= 7; i++) {
        result += (n >> i);
    }
    return result;
}

int is_cell_in_flame(char cell)
{
    return (cell & 0x00000001);
}

/*
 * 00 : Grass
 * 10 : Breakable wall
 * 11 : Unbreakable wall
 */
int get_cell_type(char cell)
{
    int result = 0;
    result += (cell >> 2 & 0x1) ? 2 : 0;
    result += (cell >> 1 & 0x1);
    return result;
}

int is_cell_bombed(char cell)
{
    return (cell >> 3 & 0x01);
}
