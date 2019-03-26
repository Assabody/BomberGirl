#ifndef     _REQUEST_H_
#define     _REQUEST_H_

typedef struct s_client_request
{
    unsigned int magic; /* Un magic number commun entre le client et le serveur, ou l’identifiant d’un type de structure */
    unsigned int x_pos; /* La position x souhaitée par le client */
    unsigned int y_pos; /* La position y souhaitée par le client */
    unsigned int dir; /* La direction souhaitée par le client */
    unsigned int command; /* Une commande du client (0 : Ne rien faire / 1 : Poser une bombe) */
    unsigned int speed; /* La vitesse du joueur */
    unsigned int checksum; /* Un checksum simple */
} t_client_request;

char *serialize_int(int);
char *serialize_char(char *, char);

int deserialize_int(char *);
char *deserialize_char(char *, char *);

void string_to_bytes(char n, char *str);
int bytes_to_int(char n);

int is_cell_in_flame(char cell);
int get_cell_type(char cell);
int is_cell_bombed(char cell);

int send_request(int, t_client_request*);


#endif