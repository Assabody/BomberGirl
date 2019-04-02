#include "../includes/main.h"

int connect_client(int sock, struct sockaddr_in *client_addr) {
    int len = sizeof(client_addr);
    return accept(sock, (struct sockaddr *) client_addr, (socklen_t * ) & len);
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
    char query[4] = {'s', 't', 'o', 'p'};
    send(game->client_sock, &query, sizeof(query), MSG_NOSIGNAL);
    sleep(1);
    pthread_cancel(game->server.server_thread);
}

void processRequest(game_infos_t *game, t_client_request request) {
    int player_key = request.magic / 16 - 1;
    // Is special request ?
    //printf("server request pos x%d y%d\n", request.x_pos, request.y_pos);
    if (request.speed == 2 * FPS) {
        // Remove bomb from the cell
        if (has_bomb(game->map[request.y_pos][request.x_pos].cell) && request.command == 0) {
            explodeBomb(game, request.x_pos, request.y_pos);
        }
    }
        // Move to new coords if possible
    else if (can_go_to_cell(game->map[request.y_pos][request.x_pos])) {
        //printf("move request\n");
        map_coords_to_player_coords(request.x_pos, request.y_pos, &game->players[player_key].x_pos,
                                    &game->players[player_key].y_pos);
        // Pose bomb
        if (request.command) {
            plantBomb(game, player_key, request.x_pos, request.y_pos);
        }
    }
    game->players[player_key].current_dir = request.dir;

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
    int *server_port = (int *) arg;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket()");
        pthread_exit(NULL);
    }

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
                    } else {
                        if (number_of_clients >= MAX_PLAYERS || waiting_lobby == 0) {
                            close(new);
                        } else {
                            printf("# Server - Client connected\n");
                            send(new, &number_of_clients, sizeof(number_of_clients), MSG_NOSIGNAL);
                            game_infos.players[number_of_clients].alive = 1;
                            number_of_clients++;
                            printf("# Server - Number of clients : %d/%d\n", number_of_clients, MAX_PLAYERS);
                            printf("# Server - Send game_infos\n");
                            send(new, &game_infos, sizeof(game_infos), MSG_NOSIGNAL);
                            FD_SET(new, &active_fd_set);
                        }
                    }
                } else {
                    if (waiting_lobby) {
                        char text[4];
                        char answer;

                        if (recv(i, &text, sizeof(text), 0)) {
                            if (strncmp(text, "list", 4) == 0) {
                                answer = number_of_clients;
                                send(i, &answer, sizeof(char), MSG_NOSIGNAL);
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
                        if (!recv(i, &client_request, sizeof(client_request), 0)) {
                            printf("# Server - Client disconnected, killing him\n");
                            game_infos.players[number_of_clients].alive = 0;
                            number_of_clients--;
                            printf("# Server - Number of clients : %d/%d\n", number_of_clients, MAX_PLAYERS);
                            close(i);
                            FD_CLR(i, &active_fd_set);
                        } else {
                            if (verify_request(client_request)) {
                                processRequest(&game_infos, client_request);
                            }
                            send(i, &game_infos, sizeof(game_infos), MSG_NOSIGNAL);
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

void plantBomb(game_infos_t *game_infos, int player_key, int x, int y) {
    if (game_infos->players[player_key].bombs_left && can_pose_bomb(game_infos->map[y][x].cell)) {
        game_infos->map[y][x].cell = add_bomb_to_cell(game_infos->map[y][x].cell);
        game_infos->players[player_key].bombs_left--;
        game_infos->bombs[y][x].bomb_posed = 1;
        game_infos->bombs[y][x].player = player_key;
    }
}

void explodeBombRadius(game_infos_t *game_infos, int x, int y) {
    int player_owner = game_infos->bombs[y][x].player;
    int radius = game_infos->players[player_owner].bomb_radius;
    int stop = 0;

    printf("bomb exploded onx%d y%d\n", x, y);
    explode_cell(&game_infos->map[y][x]);
    bombCheckPlayerRadius(game_infos, x, y);
    for (int x_max = x + 1; x_max <= x + radius; x_max++) {
        if (stop) {
            break;
        }
        switch (get_cell_type(game_infos->map[y][x_max].cell)) {
            case MAP_WALL_BREAKABLE:
                //break wall and set the cell on flame
                explode_cell(&game_infos->map[y][x_max]);
                bombCheckPlayerRadius(game_infos, x_max, y);
                printf("explosion spreading to x%d y%d: wall\n", x_max, y);
                stop = 1;
                break;
            case MAP_WALL_UNBREAKABLE:
                stop = 1;
                break;
            case MAP_GRASS:
                //set the cell on flame
                explode_cell(&game_infos->map[y][x_max]);
                bombCheckPlayerRadius(game_infos, x_max, y);
                printf("explosion spreading to x%d y%d: grass\n", x_max, y);
                break;
        }
    }
    stop = 0;
    for (int x_min = x - 1; x_min >= x - radius; x_min--) {
        if (stop) {
            break;
        }
        switch (get_cell_type(game_infos->map[y][x_min].cell)) {
            case MAP_WALL_BREAKABLE:
                //break wall and set the cell on flame
                explode_cell(&game_infos->map[y][x_min]);
                bombCheckPlayerRadius(game_infos, x_min, y);
                printf("explosion spreading to x%d y%d: wall\n", x_min, y);
                stop = 1;
                break;
            case MAP_WALL_UNBREAKABLE:
                stop = 1;
                break;
            case MAP_GRASS:
                //set the cell on flame
                explode_cell(&game_infos->map[y][x_min]);
                bombCheckPlayerRadius(game_infos, x_min, y);
                printf("explosion spreading to x%d y%d: grass\n", x_min, y);
                break;
        }
    }
    stop = 0;
    for (int y_max = y + 1; y_max <= y + radius; y_max++) {
        if (stop) {
            break;
        }
        switch (get_cell_type(game_infos->map[y_max][x].cell)) {
            case MAP_WALL_BREAKABLE:
                //break wall and set the cell on flame
                explode_cell(&game_infos->map[y_max][x]);
                bombCheckPlayerRadius(game_infos, x, y_max);
                printf("explosion spreading to x%d y%d: wall\n", x, y_max);
                stop = 1;
                break;
            case MAP_WALL_UNBREAKABLE:
                stop = 1;
                break;
            case MAP_GRASS:
                //set the cell on flame
                explode_cell(&game_infos->map[y_max][x]);
                bombCheckPlayerRadius(game_infos, x, y_max);
                printf("explosion spreading to x%d y%d: grass\n", x, y_max);
                break;
        }
    }
    stop = 0;
    for (int y_min = y - 1; y_min >= y - radius; y_min--) {
        if (stop) {
            break;
        }
        switch (get_cell_type(game_infos->map[y_min][x].cell)) {
            case MAP_WALL_BREAKABLE:
                //break wall and set the cell on flame
                explode_cell(&game_infos->map[y_min][x]);
                bombCheckPlayerRadius(game_infos, x, y_min);
                printf("explosion spreading to x%d y%d: wall\n", x, y_min);
                stop = 1;
                break;
            case MAP_WALL_UNBREAKABLE:
                stop = 1;
                break;
            case MAP_GRASS:
                //set the cell on flame
                explode_cell(&game_infos->map[y_min][x]);
                bombCheckPlayerRadius(game_infos, x, y_min);
                printf("explosion spreading to x%d y%d: grass\n", x, y_min);
                break;
        }
    }
}

void bombCheckPlayerRadius(game_infos_t *game_infos, int x, int y) {
    int x_player;
    int y_player;
    for (int i = 0; i < MAX_PLAYERS; i++) {
        player_coords_to_map_coords(game_infos->players[i].x_pos, game_infos->players[i].y_pos, &x_player, &y_player);
        if (x_player == x && y_player == y) {
            if (game_infos->players[i].life - DAMAGES < 0) {
                game_infos->players[i].life = 0;
                game_infos->players[i].alive = 0;
            } else {
                game_infos->players[i].life -= DAMAGES;
            }
            printf("Player [%d] took %d damages. life before: %d, life after: %d\n", i, DAMAGES, game_infos->players[i].life + DAMAGES, game_infos->players[i].life);
        }
    }
}

void explodeBomb(game_infos_t *game_infos, int x, int y) {
    int bomb_planter;
    explodeBombRadius(game_infos, x, y);
    game_infos->map[y][x].duration = 0;
    game_infos->map[y][x].cell = grass_cell(0);
    if (game_infos->bombs[y][x].bomb_posed) {
        bomb_planter = (int) game_infos->bombs[y][x].player;
        if (game_infos->players[bomb_planter].bombs_left < game_infos->players[bomb_planter].bombs_capacity) {
            game_infos->players[bomb_planter].bombs_left++;
        }
    }
}

void initBombGrid(game_infos_t *game_infos) {
    for (int y = 0; y <= Y_MAP_SIZE; y++) {
        for (int x = 0; x <= X_MAP_SIZE; x++) {
            game_infos->bombs[y][x].player = 0;
            game_infos->bombs[y][x].bomb_posed = 0;
        }
    }
}

void init_game_infos(game_infos_t *game_infos) {
    mapInit(game_infos);
    initBombGrid(game_infos);
    initPlayer(&game_infos->players[0], 1);
    initPlayer(&game_infos->players[1], 2);
    initPlayer(&game_infos->players[2], 3);
    initPlayer(&game_infos->players[3], 4);
}
