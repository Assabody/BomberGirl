#ifndef     _REQUEST_H_
#define     _REQUEST_H_

// Structs for the messages between the server and clients
typedef struct s_client_request
{
    int client_token; /* Un magic number commun entre le client et le serveur, ou l’identifiant d’un type de structure */
    int x_pos; /* La position x souhaitée par le client */
    int y_pos; /* La position y souhaitée par le client */
    int dir; /* La direction souhaitée par le client */
    int command; /* Une commande du client (0 : Ne rien faire / 1 : Poser une bombe) */
    int speed; /* La vitesse du joueur */
    int checksum; /* Un checksum simple */
} t_client_request;

char *serialize_int(int);
char *serialize_char(char *, char);
char *serialize_request(char *, t_client_request *);

int deserialize_int(char *);
char *deserialize_char(char *, char *);
t_client_request *deserialize_request(char *, t_client_request *);

#endif