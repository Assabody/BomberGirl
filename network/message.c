#include "network.h"

/** Read a message from a socket
 *
 * @param sock
 * @return 1 = OK
 */
char* read_message(int sock, int length) {
    int n;
    char *buff;
    buff = malloc(sizeof(char) * (length + 1));
    if (sock == -1) {
        return NULL;
    }

    n = 0;
    memset(buff, '\0', length + 1);
    if ((n = recv(sock, buff, length, MSG_NOSIGNAL)) >= 0) {
        if (n == 0) {
            return NULL;
        }
        printf("Message received: %s\n",buff);
    }
    printf("Message returned: %s\n",buff);

    return buff;
}

/** send a message to a socket
 *
 * @param int sock
 * @param const char* message
 * @return 1 = OK
 */
int send_message(int sock, const char *message) {
    if (sock < 0)
        return 0;
    if (send(sock, message, strlen(message), MSG_NOSIGNAL) < 0) {
        return 1;
    } else {
        return 0;
    }
}