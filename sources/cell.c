#include "../includes/main.h"

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

int has_bomb(char cell)
{
    return ((cell >> 3) & 0x01);
}

int has_flame(char cell)
{
  return cell & 0x01;
}

int add_bomb_to_cell(char cell)
{
    return cell | 0x08;
}

int can_pose_bomb(char cell) {
    if (get_cell_type(cell) == MAP_GRASS && !has_bomb(cell)) {
        return 1;
    }
    return 0;
}

int flame_cell(char cell)
{
    return cell | 0x01;
}

void explode_cell(cell_t *cell)
{
    cell->cell = flame_cell(0);
    cell->duration = FPS / 3;
}
