#include "request.h"
#include "../includes/main.h"

char *serialize_int(int value)
{
    char *buffer = malloc(sizeof(char) * 4);
    /* Write big-endian int value into buffer; assumes 32-bit int and 8-bit char. */
    buffer[0] = value >> 16 & 0xFF;//24;
    buffer[1] = value >> 8  & 0xFF;
    buffer[2] = value       & 0xFF;
    //buffer[3] = value;
    return buffer;
}

char * serialize_char(char *buffer, char value)
{
    buffer[0] = value;
    return buffer + 1;
}

//char *cell = (char)strtol("00000000", 0, 2);


void string_to_bytes(char n, char *str)
{
    for (int i = 7; i >= 0; i--) {
        if (((n >> i) & 0x01) == 0) {
            str[i] = '0';
        } else {
            str[i] = '1';
        }
    }
}

int bytes_to_int(char n)
{
    int result = 0;
    for (int i = 0; i <= 7; i++) {
        result += (n >> i);
    }
    return result;
}

int is_cell_in_flame(char cell)
{
    return (cell & 0x00000001);
}

/*
 * 00 : Grass
 * 10 : Breakable wall
 * 11 : Unbreakable wall
 */
int get_cell_type(char cell)
{
    int result = 0;
    result += (cell >> 2 & 0x1) ? 2 : 0;
    result += (cell >> 1 & 0x1);
    return result;
}

int is_cell_bombed(char cell)
{
    return (cell >> 3 & 0x01);
}