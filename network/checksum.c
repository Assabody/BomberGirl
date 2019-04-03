#include "network.h"

unsigned char checksum (unsigned char *ptr, size_t sz) {
    unsigned char chk = 0;
    while (sz-- != 0)
        chk -= *ptr++;
    return chk;
}

int randomNumber(int lower, int upper)
{
    return (random() % (upper - lower + 1)) + lower;
}