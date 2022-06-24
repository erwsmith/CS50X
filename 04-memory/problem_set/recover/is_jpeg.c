// Detects if file is a jpeg

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover filename\n");
        return 1;
    }

    // open file
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    // read first 4 bytes
    BYTE bytes[4];
    fread(bytes, sizeof(BYTE), 4, inptr);

    if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
    {
        printf("Yes, possibly\n");
    }
    else
    {
        printf("No\n");
    }
    fclose(inptr);
}