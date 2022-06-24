#include <math.h>
#include <stdio.h>

int main(void)
{
    // printf("%f\n", pow(25, .5));

    int red[3][3];
    // test kernels
    int kernel[3][3] = {{255, 255, 255}, {255, 255, 255}, {255, 255, 255}};
    // int kernel[3][3] = {{0, 128, 255}, {0, 128, 255}, {0, 128, 255}};
    // int kernel[3][3] = {{0, 0, 0}, {128, 128, 128}, {255, 255, 255}};
    // int kernel[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    float red_factor = 0;


    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            float GxRed = 0;
            float GyRed = 0;
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    if (x + i < 0 || x + i > 2 || y + j < 0 || y + j > 2)
                    {
                        red_factor = 0;
                    }
                    else
                    {
                        red_factor = kernel[x + i][y + j];
                    }
                    // printf("%i ", red_factor);
                    // printf("%i ", Gx[x + 1][y + 1]);
                    // printf("%i ", Gy[x + 1][y + 1]);
                    // printf("%f ", Gx[x + 1][y + 1] * red_factor);
                    GxRed += Gx[x + 1][y + 1] * red_factor;
                    GyRed += Gy[x + 1][y + 1] * red_factor;
                }
                // printf("\n");
            }
            // printf("\n\n");
            float t = .1;
            red[i][j] = round(pow((pow(GxRed, 2) + pow(GyRed, 2)), .5)) * t;

            if (red[i][j] > 255)
            {
                red[i][j] = 255;
            }
            printf("[%i][%i] %i\t", i, j, red[i][j]);
        }
        printf("\n");
    }
}