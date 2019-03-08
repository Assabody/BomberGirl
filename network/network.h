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

#define MAP_SIZE 16
#define MAX_PLAYERS 4

int send_message(int sock, const char *message);
int read_message(int sock);
int connect_client(int sock, struct sockaddr_in *client_addr);
int initClient(char *address, char *port);


// Structs for the messages between the server and clients
typedef struct s_client_request
{
    unsigned int client_token; /* Un magic number commun entre le client et le serveur, ou l’identifiant d’un type de structure */
    int x_pos; /* La position x souhaitée par le client */
    int y_pos; /* La position y souhaitée par le client */
    int dir; /* La direction souhaitée par le client */
    int command; /* Une commande du client (0 : Ne rien faire / 1 : Poser une bombe) */
    int speed; /* La vitesse du joueur */
    int ckecksum; /* Un checksum simple */
} t_client_request;

// Checksum.c
unsigned int randomNumber(unsigned int, unsigned int);

#endif //_NETWORK_H_
