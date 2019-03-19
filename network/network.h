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

#define X_MAP_SIZE 15
#define Y_MAP_SIZE 13
#define MAX_PLAYERS 4
#define MAP_WALL_BREAKABLE 'w'
#define MAP_WALL_UNBREAKABLE 'x'
#define MAP_GRASS 'g'
#define MAP_BOMB 'b'


int send_message(int, const char *);
char *read_message(int, int);
int connect_client(int, struct sockaddr_in *);

// Checksum.c
int randomNumber(int, int);

#endif //_NETWORK_H_
