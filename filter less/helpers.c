#include "helpers.h"
#include <math.h>
#include <string.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE average = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = (BYTE) round((((double) image[i][j].rgbtBlue +  image[i][j].rgbtGreen +  image[i][j].rgbtRed) / 3));
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed = 0;
    int sepiaGreen = 0;
    int sepiaBlue = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // calculate sepia values
            sepiaRed = (int) round((.393 * (float) image[i][j].rgbtRed + .769 * (float) image[i][j].rgbtGreen + .189 *
                                    (float) image[i][j].rgbtBlue));
            sepiaGreen = (int) round((.349 * (float) image[i][j].rgbtRed + .686 * (float) image[i][j].rgbtGreen + .168 *
                                      (float) image[i][j].rgbtBlue));
            sepiaBlue = (int) round((.272 * (float) image[i][j].rgbtRed + .534 * (float) image[i][j].rgbtGreen + .131 *
                                     (float) image[i][j].rgbtBlue));

            // normalize sepia values to 8 bits
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // put values into array
            image[i][j].rgbtRed = (BYTE) sepiaRed;
            image[i][j].rgbtGreen = (BYTE) sepiaGreen;
            image[i][j].rgbtBlue = (BYTE) sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buffer;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            buffer = image[i][j];
            image[i][j] = image[i][(width - 1) - j];
            image[i][(width - 1) - j] = buffer;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // make a copy of image
    double bufferR1[height][width];
    double bufferG1[height][width];
    double bufferB1[height][width];
    RGBTRIPLE vertical[height][width];

    RGBTRIPLE average;

    // im gonna make two by two for loops, one will copy some values to a copy image, the other will combine the final
    // values into the end image

    // first loop will sum the values horizontally
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // in case its the column on the left
            if (j == 0)
            {
                bufferR1[i][j] = (((double) image[i][j].rgbtRed + image[i][j + 1].rgbtRed) / 2);
                bufferG1[i][j] = (((double) image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen) / 2);
                bufferB1[i][j] = (((double) image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue) / 2);
            }
            // in case its the column on the right
            else if (j == width - 1)
            {
                bufferR1[i][j] = (((double) image[i][j].rgbtRed + image[i][j - 1].rgbtRed) / 2);
                bufferG1[i][j] = (((double) image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen) / 2);
                bufferB1[i][j] = (((double) image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue) / 2);
            }
            // any column in the middle
            else
            {
                bufferR1[i][j] = (((double) image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed) / 3);
                bufferG1[i][j] = (((double) image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen) / 3);
                bufferB1[i][j] = (((double) image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue) / 3);
            }
        }
    }

    // this loop will average digits vertically
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // in case its the first row
            if (i == 0)
            {
                vertical[i][j].rgbtRed = (BYTE) round((bufferR1[i][j] + bufferR1[i + 1][j]) / 2);
                vertical[i][j].rgbtGreen = (BYTE) round((bufferG1[i][j] + bufferG1[i + 1][j]) / 2);
                vertical[i][j].rgbtBlue = (BYTE) round((bufferB1[i][j] + bufferB1[i + 1][j]) / 2);
            }
            // in case its the last row
            else if (i == height - 1)
            {
                vertical[i][j].rgbtRed = (BYTE) round((bufferR1[i][j] + bufferR1[i - 1][j]) / 2);
                vertical[i][j].rgbtGreen = (BYTE) round((bufferG1[i][j] + bufferG1[i - 1][j]) / 2);
                vertical[i][j].rgbtBlue = (BYTE) round((bufferB1[i][j] + bufferB1[i - 1][j]) / 2);
            }
            // any other row in the middle
            else
            {
                vertical[i][j].rgbtRed = (BYTE) round((bufferR1[i][j] + bufferR1[i - 1][j] + bufferR1[i + 1][j]) / 3);
                vertical[i][j].rgbtGreen = (BYTE) round((bufferG1[i][j] + bufferG1[i - 1][j] + bufferG1[i + 1][j]) / 3);
                vertical[i][j].rgbtBlue = (BYTE) round((bufferB1[i][j] + bufferB1[i - 1][j] + bufferB1[i + 1][j]) / 3);
            }
        }
    }

    memcpy(image, vertical, sizeof(RGBTRIPLE) * height * width);
    return;
}
