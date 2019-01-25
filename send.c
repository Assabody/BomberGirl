#include "send.h"


int    sendMessage(int sock)
{
    char message[128];

    while (1) {
        memset(message, '\0', 128);
        puts("message to send:");
        fgets(message, 128, stdin);
        if (strncmp("exit", message, 5) == 0) {
            puts("end of program");
            return 0;
        } else if (send(sock, message, strlen(message), 0) < 0) {
            puts("send failed");
            return 1;
        }
        printf("sended %s\n", message);
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

    puts("enter server IP");
    fgets(ip, 22, stdin);
    puts("enter server Port");
    fgets(port, 6, stdin);
    puts("tape exit to quit program");

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
