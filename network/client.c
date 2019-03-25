#include "network.h"
#include "../includes/main.h"
#include "server.h"

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

void getMap(int socket, game_t *game)
{
    game_infos_t game_infos;
    recv(socket, &game_infos, sizeof(game_infos), MSG_CONFIRM);
    int y = 0;
    int x = 0;
    for (int i = 0; i <= X_MAP_SIZE * Y_MAP_SIZE; ++i) {
        printf("x %d - y %d : %d\n", x, y, i % X_MAP_SIZE);
        if (i % X_MAP_SIZE == 0) {
            if (i != 0) {
                printf("y++\n");
                y++;
                x = 0;
            }
        }
        game->map[y][x].cell = game_infos.map[y][x].cell;
        game->map[y][x].bomb_timing = game_infos.map[y][x].bomb_timing;
        x++;
    }
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
    char *result = read_message(sockfd, 4);
    puts(result);
    if (!result || strncmp(result, "pong", 4) != 0 ) {
        return -1;
    }
    getMap(sockfd, game);
    print_map(game);
    printf("\ncell in game->map %d\n", game->map[0][0].cell);

    return sockfd;
}
