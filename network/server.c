#include "../includes/main.h"
#include "server.h"


int connect_client(int sock, struct sockaddr_in *client_addr) {
    int len = sizeof(client_addr);
    return accept(sock, (struct sockaddr *) client_addr, (socklen_t*)&len);
}

int main() {
    int sock;
    int client1;
    int client2;
    int client_addr_len;
    int number_of_clients;
    int max_number_of_clients;
    struct sockaddr_in server;
    struct sockaddr_in client_addr;
    int i;
    fd_set active_fd_set, read_fd_set;
    struct timeval timeout;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket()");
        return 1;
    }
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    if (setsockopt (sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,
                    sizeof(timeout)) < 0)
        perror("setsockopt()");

    if (setsockopt (sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,
                    sizeof(timeout)) < 0)
        perror("setsockopt()");

    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_family = AF_INET;
    server.sin_port = htons(1234);

    if (bind(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("bind()");
        return 1;
    }

    listen(sock, 2);
    FD_ZERO(&active_fd_set);
    FD_SET(sock, &active_fd_set);
    number_of_clients = 0;
    max_number_of_clients = 4;
    game_infos_t game_infos;
    init_game_infos(&game_infos);
    printf("Number of clients : %d/%d\n", number_of_clients, max_number_of_clients);
    while (1) {
        read_fd_set = active_fd_set;
        if (select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0) {
            perror("select");
            exit(-1);
        }
        for (i = 0; i < FD_SETSIZE; ++i) {
            if (FD_ISSET(i, &read_fd_set)) {
                if (i == sock) {
                    int new;
                    if ((new = connect_client(sock, &client_addr)) < 0) {
                        perror("accept");
                        exit(EXIT_FAILURE);
                    }
                    else {
                        if (number_of_clients >= max_number_of_clients) {
                            close(new);
                        } else {
                            printf("Client connected\n");
                            puts("send token\n");
                            send(new, &number_of_clients, sizeof(number_of_clients), 0);
                            number_of_clients++;
                            printf("Number of clients : %d/%d\n", number_of_clients, max_number_of_clients);
                            puts("send game_infos\n");
                            send(new, &game_infos, sizeof(game_infos), 0);
                            FD_SET(new, &active_fd_set);
                        }
                    }
                } else {
                    t_client_request client_request;
                    puts("recv client_request\n");
                    if (!recv(i, &client_request, sizeof(client_request), 0)) {
                        printf("Client disconnected\n");
                        number_of_clients--;
                        printf("Number of clients : %d/%d\n", number_of_clients, max_number_of_clients);
                        close(i);
                        FD_CLR(i, &active_fd_set);
                    } else {
                        printf("magic number %d\n", client_request.magic);
                        if (client_request.y_pos < Y_MAP_SIZE && client_request.x_pos < X_MAP_SIZE) {
                            int player_key = client_request.magic / 16 - 1;
                            //= (game->player.token + 1) * 16;

                            printf("player_key %d moving to x %d y %d? %s\n", player_key, client_request.x_pos, client_request.y_pos, can_go_to_cell(game_infos.map[client_request.y_pos][client_request.x_pos]) ? "ok" : "ko");
                            if (can_go_to_cell(game_infos.map[client_request.y_pos][client_request.x_pos])) {
                                map_coords_to_player_coords(client_request.x_pos, client_request.y_pos, &game_infos.players[player_key].x_pos, &game_infos.players[player_key].y_pos);
                                printf("moved to x %d y %d?\n", game_infos.players[player_key].x_pos, game_infos.players[player_key].y_pos);
                            }
                            printf("request received: pose_bomb %d\n", client_request.command);
                        } else {
                            printf("moving to x %d y %d? %s\n", client_request.x_pos, client_request.y_pos, "bad coords");
                        }
                        puts("send game_infos\n");
                        send(i, &game_infos, sizeof(game_infos), 0);
                    }
                }
            }
        }
    }
    close(sock);
    return 0;
}

void init_game_infos(game_infos_t *game_infos)
{
    mapInit(game_infos);

    initPlayer(&game_infos->players[0], 1);
    initPlayer(&game_infos->players[1], 2);
    initPlayer(&game_infos->players[2], 3);
    initPlayer(&game_infos->players[3], 4);
}