#include "helpers.h"
#include <math.h>

// void red_filter(int height, int width, RGBTRIPLE image [height][width])
// {
//     for (int i = 0; i < height; i++)
//     {
//         for (int j = 0; j < width; j++)
//         {
//             image[i][j].rgbtBlue = 0x00;
//             image[i][j].rgbtGreen = 0x00;
//         }
//     }
//     return;
// }

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // get average value (float) of RGB in pixel, round to nearest int
            avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // cap sum at 255
            if (avg > 255)
            {
                avg = 255;
            }
            // set all color values to avg value
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < floor(width / 2); j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    // create copy of each original pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // for each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float red_sum = 0;
            float green_sum = 0;
            float blue_sum = 0;
            int counter = 0;

            // check 3x3 'kernel' around pixel i,j
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    // if pixel i + x, j + y is out of bounds, skip to next pixel in kernel
                    if (i + x < 0 || i + x > height - 1 || j + y < 0 || j + y > width - 1)
                    {
                        continue;
                    }
                    // if pixel is in bounds, add to sums
                    red_sum     += copy[i + x][j + y].rgbtRed;
                    green_sum   += copy[i + x][j + y].rgbtGreen;
                    blue_sum    += copy[i + x][j + y].rgbtBlue;
                    counter++;
                }
            }
            // set pixel values to 3x3 kernel average
            image[i][j].rgbtRed   = round(red_sum   / counter);
            image[i][j].rgbtGreen = round(green_sum / counter);
            image[i][j].rgbtBlue  = round(blue_sum  / counter);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    // create copy of original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed   = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue  = image[i][j].rgbtBlue;
        }
    }

    // define G convolution matrices
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // initialize factor variables
    float red_factor = 0;
    float green_factor = 0;
    float blue_factor = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // reset Gx values
            float GxRed = 0;
            float GxGreen = 0;
            float GxBlue = 0;
            float GyRed = 0;
            float GyGreen = 0;
            float GyBlue = 0;

            // check 3x3 'kernel' around pixel i,j
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    // if pixel at i + x, j + y is out of bounds, set factor to black
                    if (i + x < 0 || i + x > height - 1 || j + y < 0 || j + y > width - 1)
                    {
                        red_factor      = 0;
                        green_factor    = 0;
                        blue_factor     = 0;
                    }
                    else
                    {
                        red_factor      = copy[i + x][j + y].rgbtRed;
                        green_factor    = copy[i + x][j + y].rgbtGreen;
                        blue_factor     = copy[i + x][j + y].rgbtBlue;
                    }
                    // calculate kernel's Gx sums
                    GxRed   += Gx[x + 1][y + 1] * red_factor;
                    GxGreen += Gx[x + 1][y + 1] * green_factor;
                    GxBlue  += Gx[x + 1][y + 1] * blue_factor;

                    // calculate kernel's Gy sums
                    GyRed   += Gy[x + 1][y + 1] * red_factor;
                    GyGreen += Gy[x + 1][y + 1] * green_factor;
                    GyBlue  += Gy[x + 1][y + 1] * blue_factor;
                }
            }

            // calculate new color values
            int red     = round(pow((pow(GxRed,     2) + pow(GyRed,     2)), .5));
            int green   = round(pow((pow(GxGreen,   2) + pow(GyGreen,   2)), .5));
            int blue    = round(pow((pow(GxBlue,    2) + pow(GyBlue,    2)), .5));

            // cap all values at 255
            if (red >= 255)
            {
                red = 255;
            }
            if (green >= 255)
            {
                green = 255;
            }
            if (blue >= 255)
            {
                blue = 255;
            }

            // set final color values
            image[i][j].rgbtRed   = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue  = blue;
        }
    }
    return;
}
