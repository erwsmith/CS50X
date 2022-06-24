// counts jpeg files in card.raw
// usage: ./count_jpeg card.raw

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    FILE *inptr = fopen(argv[1], "r");
    int jpeg_count = 0;
    int BLOCK_SIZE = 512;
    BYTE buffer[BLOCK_SIZE];

    while (fread(buffer, 1, BLOCK_SIZE, inptr) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            jpeg_count++;
        }
    }
    fclose(inptr);
    printf("jpeg count: %i\n", jpeg_count);
}
