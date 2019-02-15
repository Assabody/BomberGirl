#include "network.h"

/** Read a message from a socket
 *
 * @param sock
 * @return 1 = OK
 */
int read_message(int sock) {
    int n;
    char buff[128];
    if (sock == -1) {
        return 0;
    }

    n = 0;
    memset(buff, '\0', 128);
    while ((n = recv(sock, buff, 128, 0)) >= 0) {
        if (n == 0) {
            return -1;
        }
        printf("'%s'\n", buff);
        if (buff[n - 1] == '\n') {
            memset(buff, '\0', 128);
            break;
        }
    }
    return 1;
}

/** send a message to a socket
 *
 * @param int sock
 * @param const char* message
 * @return 1 = OK
 */
int send_message(int sock, const char *message) {
    if (send(sock, message, strlen(message), MSG_NOSIGNAL) < 0) {
        return 1;
    } else {
        return 0;
    }
}