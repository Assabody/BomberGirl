#include "request.h"
#include "../includes/main.h"

int send_request(int socket, int client_token, t_client_request *request) {
    request->magic = (client_token + 1) * 16;
    printf("Sending request to server...\n");
    printf("Request content:\n");
    printf("  MAGIC:%d\n", request->magic);
    printf("  Y_POS:%d\n", request->y_pos);
    printf("  X_POS:%d\n", request->x_pos);
    printf("  COMMAND:%d\n", request->command);
    printf("  SPEED:%d\n", request->speed);
    printf("  DIR:%d\n", request->dir);
    request->checksum = request->dir + request->speed + request->command + request->x_pos + request->y_pos + request->magic;
    printf("#checksum (%d)\n", request->checksum);

    if (send(socket, request, sizeof(*request), 0)) {
        request->magic = 0;
        request->command = 0;
        return 1;
    }
    return 0;
}

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

int verify_request(t_client_request request) {
    return (request.checksum == request.magic + request.y_pos + request.x_pos + request.command + request.speed + request.dir);
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
