#include "network.h"

int    sendMessage(int sock)
{
    char message[10];

    while (1) {
        memset(message, '\0', 10);
        puts("message to send:");
        fgets(message, 10, stdin);
        if (strncmp("exit", message, 4) == 0) {
            puts("end of program");
            return 0;
        } else if (send(sock, message, strlen(message), MSG_NOSIGNAL) < 0) {
            puts("send failed");
            return 1;
        } else {
            printf("message sent: '%s'\n", message);
        }
    }
}


int   main()
{
    int sock;
    struct sockaddr_in server;
    int error;
    char ip[22];
    char port[6];


    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket()");
        exit(errno);
    }

    puts("enter server address");
    fgets(ip, 22, stdin);
    puts("enter server Port");
    fgets(port, 6, stdin);
    puts("type exit to quit program");

    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(port));
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("connect()");
        exit(errno);
    }

    error = sendMessage(sock);
    close(sock);
    return error;
}
