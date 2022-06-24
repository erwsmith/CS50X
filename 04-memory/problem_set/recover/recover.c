#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover filename\n");
        return 1;
    }

    // Open input file (memory card) if it can be opened
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    // initialize variables
    int jpeg_count = 0;
    int BLOCK_SIZE = 512;
    BYTE buffer[BLOCK_SIZE];
    char *filename = malloc(8 * sizeof(char));
    FILE *img = NULL;

    // read entire card file
    while (fread(buffer, 1, BLOCK_SIZE, inptr) == BLOCK_SIZE)
    {
        // if a jpeg is found (based on values of first 4 bytes)
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if a jpeg has already been found, close the current image file
            if (jpeg_count != 0)
            {
                fclose(img);
            }

            // create, open, and validate a new jpeg file
            sprintf(filename, "%03i.jpg", jpeg_count);
            img = fopen(filename, "w");
            if (img == NULL)
            {
                return 1;
            }

            // increment jpeg counter
            jpeg_count++;
        }

        // if a jpeg has been found, write block to current jpeg file
        if (jpeg_count > 0)
        {
            fwrite(buffer, 1, BLOCK_SIZE, img);
        }
    }
    // close all files and free memory
    fclose(inptr);
    fclose(img);
    free(filename);
    return 0;
}