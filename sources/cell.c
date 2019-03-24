#include "../includes/cell.h"

int grass_cell(char cell)
{
    return cell | 0x00;
}

int breakable_wall_cell(char cell)
{
    return cell | 0x06;
}

int unbreakable_wall_cell(char cell)
{
    return cell | 0x02;
}