#include <math.h>
#include <stdio.h>

void grayscale(int height, int width, int x, int y, int z);

int main(void)
{
    grayscale(10, 10, 100, 100, 99);
}

void grayscale(int height, int width, int x, int y, int z)
{
    int avg;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // get average value of RGB in pixel, round to nearest int
            avg = round((x + y + z) / 3.0);

            // cap sum at 255
            if (avg > 255)
            {
                avg = 255;
            }

            x = avg;
            y = avg;
            z = avg;
        }
    }
    printf("%i\n", x);
    return;
}