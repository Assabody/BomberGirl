#include "network.h"
#include "../includes/main.h"
#include "server.h"

int getServerInfo(int socket, game_t *game)
{
    int x;
    int y;
    map_coords_to_player_coords(X_MAP_SIZE, Y_MAP_SIZE, &x, &y);
    game_infos_t game_infos;
    if (recv(socket, &game_infos, sizeof(game_infos), 0)) {
        if (game_infos.players[game->player_key].x_pos > 0 && game_infos.players[game->player_key].y_pos > 0 && game_infos.players[game->player_key].x_pos < x && game_infos.players[game->player_key].y_pos < y) {
            int y = 0;
            int x = 0;
            for (int i = 0; i <= X_MAP_SIZE * Y_MAP_SIZE; ++i) {
                if (i % X_MAP_SIZE == 0) {
                    if (i != 0) {
                        y++;
                        x = 0;
                    }
                }
                game->map[y][x].cell = game_infos.map[y][x].cell;
                /*if (has_bomb(game->map[y][x].cell) && game->map[y][x].duration == 0) {
                    game->map[y][x].duration = 2 * FPS;
                } else {*/
                    game->map[y][x].duration = game_infos.map[y][x].duration;
                //}
                x++;
            }
            for (int i = 0; i < MAX_PLAYERS; i++) {
                if (game_infos.players[i].alive) {
                    game->player[i].x_pos = game_infos.players[i].x_pos;
                    game->player[i].y_pos = game_infos.players[i].y_pos;
                    game->player[i].alive = game_infos.players[i].alive;
                    game->player[i].current_speed = game_infos.players[i].current_speed;
                    game->player[i].max_speed = game_infos.players[i].max_speed;
                    game->player[i].bombs_left = game_infos.players[i].bombs_left;
                    game->player[i].bombs_capacity = game_infos.players[i].bombs_capacity;
                }

            }
            //printf("New player coords x%d y%d\n", game->player[game->player_key].x_pos, game->player[game->player_key].y_pos);
            return 1;
        }
    }
    return 0;
}

int initClient(char *address, char *port, game_t *game)
{
    int sockfd, portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    sockfd = -1;
    printf("initClient port %s\n", port);
    portno = atoi(port);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        puts("ERROR opening socket");
    server = gethostbyname(address);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        return -1;
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        puts("ERROR connecting");
        close(sockfd);
        return -1;
    }
    send_message(sockfd, "ping");
    recv(sockfd, &game->player_key, sizeof(int), 0);
    printf("token received from the server is %d\n", game->player_key);
    if (!getServerInfo(sockfd, game))
        return -1;
    return sockfd;
}

void quit_client(int socket) {
    close(socket);
}