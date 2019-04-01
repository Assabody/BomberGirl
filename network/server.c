#include "../includes/main.h"

int connect_client(int sock, struct sockaddr_in *client_addr) {
    int len = sizeof(client_addr);
    return accept(sock, (struct sockaddr *) client_addr, (socklen_t*)&len);
}

void startServer(game_t *game, int *port) {
    printf("Creation du thread server.\n");
    if (pthread_create(&game->server.server_thread, NULL, server, (void *) port)) {
        perror("pthread_create");
        free(port);
    } else {
        game->server.started = 1;
    }
}

void stopServer(game_t *game) {
    int result = -9;

    char query[4] = {'s','t','o','p'};
    send(game->client_sock, &query, sizeof(query), 0);

    printf("pthread_join\n");
    pthread_join(game->server.server_thread, (void *)&result);
    printf("Server result %d\n", result);
}

void *server(void *arg) {
    int sock;
    int number_of_clients;
    struct sockaddr_in server;
    struct sockaddr_in client_addr;
    int i;
    int running;
    int waiting_lobby;
    fd_set active_fd_set, read_fd_set;
    struct timeval timeout;
    int *server_port = (int*) arg;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket()");
        pthread_exit(NULL);
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
    server.sin_port = htons(*server_port);

    if (bind(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("bind()");
        pthread_exit(NULL);
    }

    listen(sock, 2);
    FD_ZERO(&active_fd_set);
    FD_SET(sock, &active_fd_set);
    number_of_clients = 0;
    game_infos_t game_infos;
    waiting_lobby = 1;
    running = 1;
    init_game_infos(&game_infos);
    printf("# Server - Number of clients : %d/%d\n", number_of_clients, MAX_PLAYERS);
    while (running) {
        read_fd_set = active_fd_set;
        if (select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0) {
            perror("select");
            pthread_exit(NULL);
        }
        for (i = 0; i < FD_SETSIZE; ++i) {
            if (FD_ISSET(i, &read_fd_set)) {
                if (i == sock) {
                    int new;
                    if ((new = connect_client(sock, &client_addr)) < 0) {
                        perror("accept");
                        pthread_exit(NULL);
                    }
                    else {
                        if (number_of_clients >= MAX_PLAYERS || waiting_lobby == 0) {
                            close(new);
                        } else {
                            printf("# Server - Client connected\n");
                            printf("# Server - Send token\n");
                            send(new, &number_of_clients, sizeof(number_of_clients), 0);
                            game_infos.players[number_of_clients].alive = 1;
                            number_of_clients++;
                            printf("# Server - Number of clients : %d/%d\n", number_of_clients, MAX_PLAYERS);
                            printf("# Server - In the game\n");
                            printf("# Server - Send game_infos\n");
                            send(new, &game_infos, sizeof(game_infos), 0);
                            FD_SET(new, &active_fd_set);
                        }
                    }
                } else {
                    if (waiting_lobby) {
                        char text[4];
                        char answer;

                        if (recv(i, &text, sizeof(text), 0)) {
                            printf("# Server - in lobby, received %s, there is %d clients\n", text, number_of_clients);
                            if (strncmp(text, "list", 4) == 0) {
                                answer = number_of_clients;
                                send(i, &answer, sizeof(char), 0);
                            } else if (strncmp(text, "stop", 4) == 0) {
                                printf("# Server - Leaving lobby and stopping server...\n");
                                running = 0;
                            } else if (strncmp(text, "play", 4) == 0) {
                                printf("# Server - Leaving lobby and starting game...\n");
                                waiting_lobby = 0;
                            }
                        }
                    } else {
                        t_client_request client_request;
                        puts("# Server - receiving game_infos\n");
                        if (!recv(i, &client_request, sizeof(client_request), 0)) {
                            printf("# Server - Client disconnected, killing him\n");
                            game_infos.players[number_of_clients].alive = 0;
                            number_of_clients--;
                            printf("# Server - Number of clients : %d/%d\n", number_of_clients, MAX_PLAYERS);
                            close(i);
                            FD_CLR(i, &active_fd_set);
                        } else {
                            printf("== Request received ==\n");
                            if (verify_request(client_request)) {
                                int player_key = client_request.magic / 16 - 1;
                                printf("Request sent by player [%d]\n", player_key);
                                printf("  x_pos %d\n  y_pos %d\n", client_request.x_pos, client_request.y_pos);
                                if (can_go_to_cell(game_infos.map[client_request.y_pos][client_request.x_pos])) {
                                    map_coords_to_player_coords(client_request.x_pos, client_request.y_pos, &game_infos.players[player_key].x_pos, &game_infos.players[player_key].y_pos);
                                }
                                printf("player at [X]%d  [Y]%d (%d %d)\n", game_infos.players[player_key].x_pos, game_infos.players[player_key].y_pos, client_request.x_pos, client_request.y_pos);
                                if (client_request.command == 1)
                                    printf("pose bomb\n");
                            } else {
                                printf("# Server - bad request data (checksum)\n");
                            }
                            printf("==   End Request   ==\n");
                            puts("# Server - sending game_infos\n");
                            send(i, &game_infos, sizeof(game_infos), 0);
                        }
                    }
                    if (number_of_clients <= 0) {
                        printf("# Server - No player connected, stopping server...\n");
                        running = 0;
                    }
                }
            }
        }
    }
    close(sock);
    pthread_exit(NULL);
}

void init_game_infos(game_infos_t *game_infos)
{
    mapInit(game_infos);

    initPlayer(&game_infos->players[0], 1);
    initPlayer(&game_infos->players[1], 2);
    initPlayer(&game_infos->players[2], 3);
    initPlayer(&game_infos->players[3], 4);
}
