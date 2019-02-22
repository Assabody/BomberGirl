#include "network.h"

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int initClient(char *address, char *port)
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    portno = atoi(port);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname(address);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        error("ERROR connecting");
        close(sockfd);
    }
    return sockfd;
}


/*
int main(int argc, char *argv[])
{
    char buffer[256];
    int client_sock = -1;

    client_sock = initClient("localhost", "1234");
    while(1)
    {
        printf("Client: ");
        bzero(buffer,256);
        fgets(buffer,255,stdin);
        if (strncmp(buffer, "quit", 4) == 0) {
            break;
        }
        send_message(client_sock,buffer);
        read_message(client_sock);
    }
    close(client_sock);
    return 0;
}
*/
