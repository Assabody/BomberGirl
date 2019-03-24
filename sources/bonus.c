#include "../includes/main.h"
#include "../includes/bonus.h"

int cell_has_bonus(char cell)
{
    return (cell >> 4 & 0x1);
}

int get_bonus(char cell)
{
    unsigned int bonus_representation = 0;

    bonus_representation += (cell >> 5) & 0x1;
    bonus_representation += ((cell >> 6) & 0x1) * 2;
    bonus_representation += ((cell >> 7) & 0x1) * 4;
    return bonus_representation;
}