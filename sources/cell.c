#include "../includes/main.h"

/**
 * Byte Manipulation
 */
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

/**
 * Getters
 */
int is_grass(unsigned char cell)
{
    return !test_byte(cell, 1) && !test_byte(cell, 2);
}

int is_breakable(unsigned char cell)
{
    return test_byte(cell, 1) && test_byte(cell, 2);
}

int is_unbreakable(unsigned char cell)
{
    return test_byte(cell, 1);
}

int is_bomb(unsigned char cell)
{
    return test_byte(cell, 3);
}

int is_flame(unsigned char cell)
{
    return test_byte(cell, 0);
}

int is_bonus(unsigned char cell)
{
    return test_byte(cell, 4);
}

int get_bonus(unsigned char cell)
{
    return cell >> 5;
}
/**
 * Setters
 */
void set_grass(unsigned char *cell)
{
    clear_byte(cell, 1);
    clear_byte(cell, 2);
}

void set_breakable(unsigned char *cell)
{
    toggle_byte(cell, 1);
    toggle_byte(cell, 2);
}

void set_unbreakable(unsigned char *cell)
{
    toggle_byte(cell, 1);
    clear_byte(cell, 2);
}

void set_bomb(unsigned char *cell, int set)
{
    if (set) {
        toggle_byte(cell, 3);
    } else {
        clear_byte(cell, 3);
    }
}

void set_flame(unsigned char *cell, int set)
{
    if (set)
    {
        toggle_byte(cell, 0);
    }
    else
    {
        clear_byte(cell, 0);
    }
}

void remove_bonus(unsigned char *cell)
{
    clear_byte(cell, 4);
    clear_byte(cell, 5);
    clear_byte(cell, 6);
    clear_byte(cell, 7);
}

void set_bonus(unsigned char *cell, int bonus)
{
    toggle_byte(cell, 4);             // has bonus
    *cell = *cell | (bonus << 5); // le bonus est l'int
}

// Others
int can_pose_bomb(unsigned char cell)
{
    if (get_cell_type(cell) == MAP_GRASS && !is_bomb(cell)) {
        return 1;
    }
    return 0;
}

void explode_cell(cell_t *cell)
{
    if (is_grass(cell->cell)) {
        remove_bonus(&cell->cell);
    }
    set_grass(&cell->cell);
    set_bomb(&cell->cell, 0);
    set_flame(&cell->cell, 1);
    cell->duration = FPS / 3;
}