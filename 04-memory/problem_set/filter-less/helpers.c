#include "helpers.h"
#include <math.h>

// image[0] is first row
// image[height - 1] is last row
// image[0][0] is first pixel
// image[0][width - 1] is last pixel in first row
// make pixel 0,0 black:
// image[0][0].rgbtRed = 0;
// image[0][0].rgbtGreen = 0;
// image[0][0].rgbtBlue = 0;

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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int green = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int blue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }

            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
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
            int red   = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue  = image[i][j].rgbtBlue;

            image[i][j].rgbtRed   = image[i][width - 1 - j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtBlue  = image[i][width - 1 - j].rgbtBlue;

            image[i][width - 1 - j].rgbtRed   = red;
            image[i][width - 1 - j].rgbtGreen = green;
            image[i][width - 1 - j].rgbtBlue  = blue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    // create blurred pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed   = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue  = image[i][j].rgbtBlue;
        }
    }

    // assign blurred pixels to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i > 0 && i < height - 1 && j > 0 && j < width - 1)
                // if pixel is neither edge nor corner
            {
                image[i][j].rgbtRed = round((copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed +
                                             copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed +
                                             copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 9.0);
                image[i][j].rgbtGreen   = round((copy[i - 1][j - 1].rgbtGreen    + copy[i - 1][j].rgbtGreen +
                                                 copy[i - 1][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen +
                                                 copy[i][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen +
                                                 copy[i + 1][j + 1].rgbtGreen) / 9.0);
                image[i][j].rgbtBlue   = round((copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                                                copy[i - 1][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue +
                                                copy[i][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue +
                                                copy[i + 1][j + 1].rgbtBlue) / 9.0);
            }
            else if (i == 0 && j == 0)
            {
                // if pixel is top left corner
                image[i][j].rgbtRed   = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed +
                                               copy[i + 1][j + 1].rgbtRed) / 4.0);
                image[i][j].rgbtGreen   = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                                                 copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 4.0);
                image[i][j].rgbtBlue   = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue +
                                                copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 4.0);
            }
            else if (i == 0 && j == width - 1)
            {
                // if pixel is top right corner
                image[i][j].rgbtRed = round((copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i + 1][j - 1].rgbtRed +
                                             copy[i + 1][j].rgbtRed) / 4.0);
                image[i][j].rgbtGreen = round((copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen +
                                               copy[i + 1][j].rgbtGreen) / 4.0);
                image[i][j].rgbtBlue = round((copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue +
                                              copy[i + 1][j].rgbtBlue) / 4.0);
            }
            else if (i == height - 1 && j == 0)
            {
                // if pixel is bottom left corner
                image[i][j].rgbtRed = round((copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j].rgbtRed +
                                             copy[i][j + 1].rgbtRed) / 4.0);
                image[i][j].rgbtGreen = round((copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen +
                                               copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen) / 4.0);
                image[i][j].rgbtBlue = round((copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue +
                                              copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue) / 4.0);
            }
            else if (i == height - 1 && j == width - 1)
            {
                // if pixel is bottom right corner
                image[i][j].rgbtRed = round((copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i][j - 1].rgbtRed +
                                             copy[i][j].rgbtRed) / 4.0);
                image[i][j].rgbtGreen = round((copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen +
                                               copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen) / 4.0);
                image[i][j].rgbtBlue = round((copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i][j - 1].rgbtBlue +
                                              copy[i][j].rgbtBlue) / 4.0);
            }
            else if (i == 0 && j != 0 && j != width - 1)
            {
                // if pixel is on top edge but not a corner
                image[i][j].rgbtRed = round((copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed +
                                             copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed +
                                             copy[i + 1][j + 1].rgbtRed) / 6.0);
                image[i][j].rgbtGreen = round((copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                                               copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen +
                                               copy[i + 1][j + 1].rgbtGreen) / 6.0);
                image[i][j].rgbtBlue = round((copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue +
                                              copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue +
                                              copy[i + 1][j + 1].rgbtBlue) / 6.0);

            }
            else if (i == height - 1 && j != 0 && j != width - 1)
            {
                // if pixel is on bottom edge but not a corner
                image[i][j].rgbtRed = round((copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed +
                                             copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed) / 6.0);
                image[i][j].rgbtGreen = round((copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen +
                                               copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen) / 6.0);
                image[i][j].rgbtBlue = round((copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue +
                                              copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue) / 6.0);
            }
            else if (j == 0 && i != 0 && i != height - 1)
            {
                // if pixel is on left edge but not a corner
                image[i][j].rgbtRed = round((copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j].rgbtRed +
                                             copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 6.0);
                image[i][j].rgbtGreen = round((copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j].rgbtGreen +
                                               copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 6.0);
                image[i][j].rgbtBlue = round((copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j].rgbtBlue +
                                              copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 6.0);
            }
            else if (j == width - 1 && i != 0 && i != height - 1)
            {
                // if pixel is on right edge but not a corner
                image[i][j].rgbtRed = round((copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i][j - 1].rgbtRed +
                                             copy[i][j].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed) / 6.0);
                image[i][j].rgbtGreen = round((copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i][j - 1].rgbtGreen +
                                               copy[i][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen) / 6.0);
                image[i][j].rgbtBlue = round((copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i][j - 1].rgbtBlue +
                                              copy[i][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue) / 6.0);
            }
        }
    }
    return;
}
