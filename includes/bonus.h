/*
** ETNA PROJECT, 17/01/2019 by daurat_j
** Bomberman
** File description:
**      Header file
*/

#ifndef     _BONUS_H_
#define     _BONUS_H_

#define RANGE_BONUS 0 // 000
#define RANGE_MALUS 1 // 001
#define BOMB_NUMBER_BONUS 2 // 010
#define BOMB_NUMBER_MALUS 3 // 011
#define SPEED_BONUS 4 // 100
#define SPEED_MALUS 5 // 101

int get_bonus(char);
int cell_has_bonus(char cell);

#endif // _BONUS_H_