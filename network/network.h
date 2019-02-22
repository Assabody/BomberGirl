#ifndef _NETWORK_H_
#define _NETWORK_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>

int send_message(int sock, const char *message);
int read_message(int sock);
int connect_client(int sock, struct sockaddr_in *client_addr);
int initClient(char *address, char *port);
#endif //_NETWORK_H_
