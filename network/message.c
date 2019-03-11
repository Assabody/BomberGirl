#include "network.h"

/** Read a message from a socket
 *
 * @param sock
 * @return 1 = OK
 */
char* read_message(int sock) {
    int n;
    char *buff;
    buff = malloc(sizeof(char) * 128);
    if (sock == -1) {
        return NULL;
    }

    n = 0;
    memset(buff, '\0', 128);
    if ((n = recv(sock, buff, 128, MSG_NOSIGNAL)) >= 0) {
        if (n == 0) {
            return NULL;
        }
        printf("Message received: %s\n",buff);
    }
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
    if (send(sock, message, strlen(message), 0) < 0) {
        return 1;
    } else {
        return 0;
    }
}

int wait_for_answer(int sock, const char *expected_message) {
    int try = 1;
    while (try) {
        char *received_message = read_message(sock);
        if (received_message != NULL) {
            puts(received_message);
            if (strcmp(received_message, expected_message) == 0) {
                free(received_message);
                return 1;
            }
        }
    }
    return 0;
}