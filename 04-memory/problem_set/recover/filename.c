// generates filenames in format ###.jpg

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main(void)
{
    int jpeg_count = 10;
    for (int n = 0; n < jpeg_count; n++)
    {
        // allocate memory for jpeg filename string format: ###.jpg, save jpeg name to a string, print jpeg name, free memory
        char *s = malloc(8 * sizeof(char));
        sprintf(s, "%03i.jpg", n);
        printf("%s\n", s);
        free(s);
    }
    return 0;
}