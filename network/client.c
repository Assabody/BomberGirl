#include "network.h"

/*int    sendMessage(int sock, const char *message)
{
    if (strncmp("exit", message, 4) == 0) {
        puts("end of program");
        return -1;
    } else if (send(sock, message, strlen(message), MSG_NOSIGNAL) < 0) {
        puts("send failed");
        return 1;
    } else {
        printf("message sent: '%s'\n", message);
        return 0;
    }
}*/


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

    /*puts("enter server address");
    fgets(ip, 22, stdin);
    puts("enter server Port");
    fgets(port, 6, stdin);*/
    puts("type exit to quit program");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi("1234"));
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("connect()");
        exit(errno);
    }

    while (1) {
        send_message(sock, "client");
        //read_message(sock);
    }
    close(sock);
    return error;
}
