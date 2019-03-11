#include "request.h"

unsigned char * serialize_int(unsigned char *buffer, int value)
{
    /* Write big-endian int value into buffer; assumes 32-bit int and 8-bit char. */
    buffer[0] = value >> 24;
    buffer[1] = value >> 16;
    buffer[2] = value >> 8;
    buffer[3] = value;
    return buffer + 4;
}

unsigned char * serialize_char(unsigned char *buffer, char value)
{
    buffer[0] = value;
    return buffer + 1;
}

unsigned char * serialize_temp(unsigned char *buffer, t_client_request *value)
{
    buffer = serialize_int(buffer, value->client_token);
    buffer = serialize_int(buffer, value->x_pos);
    buffer = serialize_int(buffer, value->y_pos);
    buffer = serialize_int(buffer, value->dir);
    buffer = serialize_int(buffer, value->command);
    buffer = serialize_int(buffer, value->speed);
    buffer = serialize_int(buffer, value->checksum);
    return buffer;
}

int deserialize_int(unsigned char *buffer)
{
    printf("char %s to int\n", buffer);
    return atoi(buffer);
}

//char *cell = (char)strtol("00000000", 0, 2);