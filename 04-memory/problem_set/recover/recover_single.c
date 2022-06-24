// recovers a single image from card.raw

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

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

    int jpeg_count = 0;
    bool jpeg_found = false;
    int BLOCK_SIZE = 512;
    BYTE buffer[BLOCK_SIZE];
    char *filename = malloc(8 * sizeof(char));
    sprintf(filename, "single_image.jpg");
    FILE *img = fopen(filename, "w");
    if (img == NULL)
    {
        return 1;
    }

    while (fread(buffer, 1, BLOCK_SIZE, inptr) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            jpeg_found = true;
            if (jpeg_count == 0)
            {
                fwrite(buffer, 1, BLOCK_SIZE, img);
                jpeg_count++;
            }
        }
        else if (jpeg_found == true)
        {
            fwrite(buffer, 1, BLOCK_SIZE, img);
        }
    }
    printf("%i\n", jpeg_count);
    fclose(inptr);
    free(filename);
}