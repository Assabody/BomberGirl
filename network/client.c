#include "network.h"
#include "../includes/main.h"
#include "server.h"

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int getServerInfo(int socket, game_t *game)
{
    game_infos_t game_infos;
    puts("recv game_infos\n");
    printf("Actual client is Player [%d]\n", game->player_key);
    if (recv(socket, &game_infos, sizeof(game_infos), 0)) {
        if (game_infos.players[game->player_key].x_pos > 0 && game_infos.players[game->player_key].y_pos > 0) {
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
                game->map[y][x].bomb_timing = game_infos.map[y][x].bomb_timing;
                x++;
            }
           /* game->player[0] = game_infos.players[0];
            game->player[1] = game_infos.players[1];
            game->player[2] = game_infos.players[2];
            game->player[3] = game_infos.players[3];*/
            for (int i = 0; i < MAX_PLAYERS; i++) {
                game->player[i].x_pos = game_infos.players[i].x_pos;
                game->player[i].y_pos = game_infos.players[i].y_pos;
                game->player[i].alive = game_infos.players[i].alive;
                game->player[i].current_speed = game_infos.players[i].current_speed;
                game->player[i].max_speed = game_infos.players[i].max_speed;
                game->player[i].bombs_left = game_infos.players[i].bombs_left;
                game->player[i].bombs_capacity = game_infos.players[i].bombs_capacity;
                printf("new position for Player [%d] [X]%d [Y]%d\n", i, game_infos.players[i].x_pos, game_infos.players[i].y_pos);
            }
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
