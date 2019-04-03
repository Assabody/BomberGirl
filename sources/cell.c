#include "../includes/main.h"

void clear_byte(unsigned char *number, int n)
{
    *number &= ~(1 << n);
}

void toggle_byte(unsigned char *number, int n)
{
    *number ^= (1 << n);
}

int test_byte(unsigned char number, int n)
{
    return number &(1 << n);
}

int is_grass_cell(char cell)
{
    return cell | 0x00;
}

int is_breakable_wall_cell(char cell)
{
    return cell | 0x06;
}

int is_unbreakable_wall_cell(char cell)
{
    return cell | 0x02;
}

int is_bomb(char cell)
{
    return ((cell >> 3) & 0x01);
}

int is_flame(char cell)
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

void remove_flame(cell_t *cell)
{
    cell->cell &= 0;
}

int is_flame(char cell)
{
    return cell | 0x01;
}

void explode_cell(cell_t *cell)
{
    int bonus = get_bonus(cell->cell);
    cell->cell = flame_cell(0);
    set_bonus(cell, bonus);
    cell->duration = FPS / 3;
}

/* #define RANGE_BONUS 0       // 000
#define RANGE_MALUS 1       // 001
#define BOMB_NUMBER_BONUS 2 // 010
#define BOMB_NUMBER_MALUS 3 // 011
#define SPEED_BONUS 4       // 100
#define SPEED_MALUS 5       // 101 */

void remove_breakable_wall(cell_t *cell)
{
    cell->cell = (get_bonus(cell->cell) << 5) | (has_bonus(cell->cell) << 4);
}

void set_bonus(cell_t *cell, int bonus)
{
    cell->cell = cell->cell | (0x01 << 4);  // présence d'un bonus
    cell->cell = cell->cell | (bonus << 5); // le bonus est l'int
}

int is_bonus(char cell)
{
    return cell & (0x01 << 4);
}

int get_bonus(char cell)
{
    return cell >> 5;
}
