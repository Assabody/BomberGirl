#include "network.h"

int create_server(struct sockaddr_in *server) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket()");
        return -1;
    }

    server->sin_addr.s_addr = htonl(INADDR_ANY);
    server->sin_family = AF_INET;
    server->sin_port = htons(1234);

    if (bind(sock, (struct sockaddr *) server, sizeof(*server)) < 0) {
        perror("bind()");
        return -1;
    }
    return sock;
}

int connect_client(int sock, struct sockaddr_in *client_addr) {
    int len = sizeof(client_addr);
    return accept(sock, (struct sockaddr *) client_addr, (socklen_t*)&len);
}

int main() {
    int sock;
    int client1;
    int client2;
    int client_addr_len;
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
                    } else {
                        printf("Client connected\n");
                    }
                    FD_SET(new, &active_fd_set);
                } else {
                    int result = read_message(i);
                    if (result == -1) {
                        printf("client %s disconnected\n", inet_ntoa(client_addr.sin_addr));
                        close(i);
                        FD_CLR(i, &active_fd_set);
                    }
                }
            }
        }
    }
    close(sock);
    return 0;
}
