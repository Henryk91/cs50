#include "helpers.h"
#include <stdio.h>
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Gets avrage of rgb
            float avr = ((round(image[i][j].rgbtRed) + round(image[i][j].rgbtGreen) + round(image[i][j].rgbtBlue)) / 3);
            temp[i][j].rgbtRed = lroundl(avr);
            temp[i][j].rgbtGreen = lroundl(avr);
            temp[i][j].rgbtBlue = lroundl(avr);
        }
    }

    // Copies temp into image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // RGBTRIPLE temp;
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Save reverse of j in temp
            int reverse = (width - j) - 1;
            temp[i][j] = image[i][reverse];
        }
    }
    // Copies temp into image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Calc blur val by combining every px around main px
RGBTRIPLE blurSurroundBox(int col, int row, int height, int width, RGBTRIPLE image[height][width])
{
    int rowBefore = col - 1;
    int colBefore = row - 1;

    int pixelCount = 0;
    RGBTRIPLE average;

    average.rgbtRed = 0;
    average.rgbtGreen = 0;
    average.rgbtBlue = 0;
    float red = 0.0;
    float green = 0.0;
    float blue = 0.0;

    // Adds values of every surounding pixel in image
    for (int i = (col - 1); i <= (col + 1); i++)
    {
        for (int j = (row - 1); j <= (row + 1); j++)
        {
            if ((i >= 0 && i < height) && (j >= 0 && j < width))
            {
                red = red + (image[i][j].rgbtRed);
                green = green + (image[i][j].rgbtGreen);
                blue = blue + (image[i][j].rgbtBlue);
                pixelCount++;
            }
        }
    }
    // Get average of all pix (rgb) by deviding them by pixelCount
    average.rgbtRed = round((red / pixelCount));
    average.rgbtGreen = round((green / pixelCount));
    average.rgbtBlue = round((blue / pixelCount));

    return average;
}
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    // Get blur value for every pixel in image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = blurSurroundBox(i, j, height, width, image);
        }
    }

    // Copying temp image to new image;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Calculates from surrounding pixels and GX + GY convelutional matrix
RGBTRIPLE calcEdgePixel(int col, int row, int height, int width, RGBTRIPLE image[height][width])
{
    int rowBefore = col - 1;
    int colBefore = row - 1;

    int pixelCount = 0;
    RGBTRIPLE average;

    average.rgbtRed = 0;
    average.rgbtGreen = 0;
    average.rgbtBlue = 0;
    float red = 0;
    float green = 0;
    float blue = 0;

    float red_y = 0;
    float green_y = 0;
    float blue_y = 0;

    // Init GX + GY convelutional matrix
    int gx_vals[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int gy_vals[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

    for (int i = (col - 1); i <= (col + 1); i++)
    {
        for (int j = (row - 1); j <= (row + 1); j++)
        {
            if ((i >= 0 && i < height) && (j >= 0 && j < width))
            {
                // Calc GX and GY for surrounding pixels
                red += (image[i][j].rgbtRed * gx_vals[pixelCount]);
                green += (image[i][j].rgbtGreen * gx_vals[pixelCount]);
                blue += (image[i][j].rgbtBlue * gx_vals[pixelCount]);

                red_y += (image[i][j].rgbtRed * gy_vals[pixelCount]);
                green_y += (image[i][j].rgbtGreen * gy_vals[pixelCount]);
                blue_y += (image[i][j].rgbtBlue * gy_vals[pixelCount]);
            }
            pixelCount++;
        }
    }

    float red_a = sqrt(pow(red, 2) + pow(red_y, 2));
    float green_a = sqrt(pow(green, 2) + pow(green_y, 2));
    float blue_a = sqrt(pow(blue, 2) + pow(blue_y, 2));

    // If colors are higher than max make it max
    if (red_a > 255)
    {
        red_a = 255.0;
    }
    if (green_a > 255)
    {
        green_a = 255.0;
    }
    if (blue_a > 255)
    {
        blue_a = 255.0;
    }

    // Get average of all pix (rgb) by deviding them by pixelCount
    average.rgbtRed = round(red_a);
    average.rgbtGreen = round(green_a);
    average.rgbtBlue = round(blue_a);

    return average;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = calcEdgePixel(i, j, height, width, image);
        }
    }

    // Copying temp image to new image;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}
