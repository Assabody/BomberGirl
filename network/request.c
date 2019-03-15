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


/*int deserialize_int(char *buffer)
{
    printf("char %s to int\n", buffer);
    return atoi(buffer);
}*/

//char *cell = (char)strtol("00000000", 0, 2);