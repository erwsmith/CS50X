// creates a copy of a jpeg file

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover filename\n");
        return 1;
    }

    FILE *inptr = fopen(argv[1], "r");

    if (inptr == NULL)
    {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    int count = 0;
    int BLOCK_SIZE = 512;
    BYTE buffer[BLOCK_SIZE];
    FILE *outptr = fopen("eric_copy.jpg", "w");

    while (fread(buffer, 1, BLOCK_SIZE, inptr) > 0)
    {
        // printf("%lu\n", fread(buffer, 1, BLOCK_SIZE, inptr));
        fwrite(buffer, 1, BLOCK_SIZE, outptr);
        count++;
    }
    printf("%i blocks copied.\n", count);

    // for (int i = 0; i < 41; i++)
    // {
    //     fread(buffer, 1, BLOCK_SIZE, inptr);
    //     fwrite(buffer, 1, BLOCK_SIZE, outptr);
    // }

    fclose(inptr);
}