/*
** ETNA PROJECT, 17/01/2019 by daurat_j
** Bomberman
** File description:
**      Header file
*/

#ifndef     _SERVER_H_
#define     _SERVER_H_

#include "../includes/main.h"

/*
** Bit 0 : Indique si la case est en flammes (1) ou non (0)
** Bits [1..2] : Indique le type de terrain ( 00 : Terrain vide, 10 : Brique indestructible, 11 : Brique destructible). Note : Combinaison 01 inutilisée.
** Bit 3 : Présence d’une bombe (0 : Pas de bombe, 1 : Bombe)
** Bit 4 : Présence d’un bonus / malus (0 : Pas de bonus / malus, 1 : Bonus / malus présent)
** Bits [5..7] : Type de bonus / malus.
**
** Pour l’exemple, liste des bonus / malus
** 000 : Bonus portée bombes
** 001 : Malus portée bombes
** 010 : Bonus nombre bombes
** 011 : Malus nombre bombes
** 100 : Bonus vitesse
** 101 : Malus vitesse
** 110 : Rien
** 111 : Rien
*/

typedef struct game_infos_s
{
    player_t **players;
    char **map;
} game_infos_t;

game_infos_t *init_game_infos();

#endif
