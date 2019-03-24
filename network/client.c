#include "network.h"
#include "../includes/main.h"
#include "../includes/map.h"
#include "server.h"

void error(const char *msg)
{
    perror(msg);
    exit(0);
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
    socklen_t len = sizeof(serv_addr);
    game_infos_t *game_infos = malloc(sizeof(* game_infos));
    game_infos->map = malloc(sizeof(cell_t) * X_MAP_SIZE * Y_MAP_SIZE);
    recvfrom(sockfd, &game_infos, sizeof(game_infos), 0, (struct sockaddr *) &serv_addr, &len);
    game->map = game_infos->map;
    return sockfd;
}