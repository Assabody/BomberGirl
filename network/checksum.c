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

/*int main(int argc, char* argv[])
{
    unsigned char x[] = "Hello_";
    unsigned char y = checksum (x, 5);
    printf ("Checksum is 0x%02x\n", y); // Checksum is 0x0c
    x[5] = y;
    y = checksum (x, 6);
    printf ("Checksum test is 0x%02x\n", y); // Checksum test is 0x00 -> 0 if checksum is okay
    return 0;
}*/

//https://stackoverflow.com/questions/3463976/c-file-checksum