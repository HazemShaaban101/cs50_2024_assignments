#include "helpers.h"
#include <string.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE average;
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
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // make a copy of image
    double bufferR1[height][width];
    double bufferG1[height][width];
    double bufferB1[height][width];
    RGBTRIPLE vertical[height][width];

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
    // copy values from vertical matrix to image matrix
    memcpy(image, vertical, sizeof(RGBTRIPLE) * height * width);
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int negative = -1;
    // buffer arrays to save values of multiplication for each matrix, and for each color
    int bufferRx[height][width];
    int bufferGx[height][width];
    int bufferBx[height][width];
    int bufferRy[height][width];
    int bufferGy[height][width];
    int bufferBy[height][width];

    // top left corner
    bufferRx[0][0] = 2 * image[0][1].rgbtRed + image[1][1].rgbtRed;
    bufferGx[0][0] = 2 * image[0][1].rgbtGreen + image[1][1].rgbtGreen;
    bufferBx[0][0] = 2 * image[0][1].rgbtBlue + image[1][1].rgbtBlue;

    bufferRy[0][0] = 2 * image[1][0].rgbtRed + image[1][1].rgbtRed;
    bufferGy[0][0] = 2 * image[1][0].rgbtGreen + image[1][1].rgbtGreen;
    bufferBy[0][0] = 2 * image[1][0].rgbtBlue + image[1][1].rgbtBlue;

    // bottom left corner
    bufferRx[height - 1][0] = 2 * image[height - 1][1].rgbtRed + image[height - 2][1].rgbtRed;
    bufferGx[height - 1][0] = 2 * image[height - 1][1].rgbtGreen + image[height - 2][1].rgbtGreen;
    bufferBx[height - 1][0] = 2 * image[height - 1][1].rgbtBlue + image[height - 2][1].rgbtBlue;

    bufferRy[height - 1][0] = -2 * image[height - 2][0].rgbtRed - image[height - 2][1].rgbtRed;
    bufferGy[height - 1][0] = -2 * image[height - 2][0].rgbtGreen - image[height - 2][1].rgbtGreen;
    bufferBy[height - 1][0] = -2 * image[height - 2][0].rgbtBlue - image[height - 2][1].rgbtBlue;

    // top right
    bufferRx[0][width - 1] = (-2 * image[0][width - 2].rgbtRed) - image[1][width - 2].rgbtRed;
    bufferGx[0][width - 1] = (-2 * image[0][width - 2].rgbtGreen) - image[1][width - 2].rgbtGreen;
    bufferBx[0][width - 1] = (-2 * image[0][width - 2].rgbtBlue) - image[1][width - 2].rgbtBlue;

    bufferRy[0][width - 1] = (2 * image[1][width - 1].rgbtRed) + image[1][width - 2].rgbtRed;
    bufferGy[0][width - 1] = (2 * image[1][width - 1].rgbtGreen) + image[1][width - 2].rgbtGreen;
    bufferBy[0][width - 1] = (2 * image[1][width - 1].rgbtBlue) + image[1][width - 2].rgbtBlue;

    // bottom right
    bufferRx[height - 1][width - 1] = (-2 * image[height - 1][width - 2].rgbtRed) - image[height - 2][width - 2].rgbtRed;
    bufferGx[height - 1][width - 1] = (-2 * image[height - 1][width - 2].rgbtGreen) - image[height - 2][width - 2].rgbtGreen;
    bufferBx[height - 1][width - 1] = (-2 * image[height - 1][width - 2].rgbtBlue) - image[height - 2][width - 2].rgbtBlue;

    bufferRy[height - 1][width - 1] = (-2 * image[height - 2][width - 1].rgbtRed) - image[height - 2][width - 2].rgbtRed;
    bufferGy[height - 1][width - 1] = (-2 * image[height - 2][width - 1].rgbtGreen) - image[height - 2][width - 2].rgbtGreen;
    bufferBy[height - 1][width - 1] = (-2 * image[height - 2][width - 1].rgbtBlue) - image[height - 2][width - 2].rgbtBlue;

    // loop for horizontal sides
    for (int j = 1; j < width - 1; j++)
    {
        // upper row
        bufferRx[0][j] = (2 * image[0][j + 1].rgbtRed) - (2 * image[0][j - 1].rgbtRed) + image[1][j + 1].rgbtRed -
                         image[1][j - 1].rgbtRed;
        bufferGx[0][j] = (2 * image[0][j + 1].rgbtGreen) - (2 * image[0][j - 1].rgbtGreen) + image[1][j + 1].rgbtGreen -
                         image[1][j - 1].rgbtGreen;
        bufferBx[0][j] = (2 * image[0][j + 1].rgbtBlue) - (2 * image[0][j - 1].rgbtBlue) + image[1][j + 1].rgbtBlue -
                         image[1][j - 1].rgbtBlue;

        bufferRy[0][j] = (2 * image[1][j].rgbtRed) + image[1][j + 1].rgbtRed + image[1][j - 1].rgbtRed;
        bufferGy[0][j] = (2 * image[1][j].rgbtGreen) + image[1][j + 1].rgbtGreen + image[1][j - 1].rgbtGreen;
        bufferBy[0][j] = (2 * image[1][j].rgbtBlue) + image[1][j + 1].rgbtBlue + image[1][j - 1].rgbtBlue;

        // lower row
        bufferRx[height - 1][j] = (2 * image[height - 1][j + 1].rgbtRed) - (2 * image[height - 1][j - 1].rgbtRed) +
                                  image[height - 2][j + 1].rgbtRed - image[height - 2][j - 1].rgbtRed;
        bufferGx[height - 1][j] = (2 * image[height - 1][j + 1].rgbtGreen) - (2 * image[height - 1][j - 1].rgbtGreen) +
                                  image[height - 2][j + 1].rgbtGreen - image[height - 2][j - 1].rgbtGreen;
        bufferBx[height - 1][j] = (2 * image[height - 1][j + 1].rgbtBlue) - (2 * image[height - 1][j - 1].rgbtBlue) +
                                  image[height - 2][j + 1].rgbtBlue - image[height - 2][j - 1].rgbtBlue;

        bufferRy[height - 1][j] = (-2 * image[height - 2][j].rgbtRed) - image[height - 2][j + 1].rgbtRed -
                                  image[height - 2][j - 1].rgbtRed;
        bufferGy[height - 1][j] = (-2 * image[height - 2][j].rgbtGreen) - image[height - 2][j + 1].rgbtGreen -
                                  image[height - 2][j - 1].rgbtGreen;
        bufferBy[height - 1][j] = (-2 * image[height - 2][j].rgbtBlue) - image[height - 2][j + 1].rgbtBlue -
                                  image[height - 2][j - 1].rgbtBlue;
    }

    // loop for vertical sides
    for (int i = 1; i < height - 1; i++)
    {
        // right column
        bufferRy[i][0] = (2 * image[i + 1][0].rgbtRed) - (2 * image[i - 1][0].rgbtRed) + image[i + 1][1].rgbtRed -
                         image[i - 1][1].rgbtRed;
        bufferGy[i][0] = (2 * image[i + 1][0].rgbtGreen) - (2 * image[i - 1][0].rgbtGreen) + image[i + 1][1].rgbtGreen -
                         image[i - 1][1].rgbtGreen;
        bufferBy[i][0] = (2 * image[i + 1][0].rgbtBlue) - (2 * image[i - 1][0].rgbtBlue) + image[i + 1][1].rgbtBlue -
                         image[i - 1][1].rgbtBlue;

        bufferRx[i][0] = (2 * image[i][1].rgbtRed) + image[i + 1][1].rgbtRed + image[i - 1][1].rgbtRed;
        bufferGx[i][0] = (2 * image[i][1].rgbtGreen) + image[i + 1][1].rgbtGreen + image[i - 1][1].rgbtGreen;
        bufferBx[i][0] = (2 * image[i][1].rgbtBlue) + image[i + 1][1].rgbtBlue + image[i - 1][1].rgbtBlue;

        // left column
        bufferRy[i][width - 1] = (2 * image[i + 1][width - 1].rgbtRed) - (2 * image[i - 1][width - 1].rgbtRed) +
                                 image[i + 1][width - 2].rgbtRed - image[i - 1][width - 2].rgbtRed;
        bufferGy[i][width - 1] = (2 * image[i + 1][width - 1].rgbtGreen) - (2 * image[i - 1][width - 1].rgbtGreen) +
                                 image[i + 1][width - 2].rgbtGreen - image[i - 1][width - 2].rgbtGreen;
        bufferBy[i][width - 1] = (2 * image[i + 1][width - 1].rgbtBlue) - (2 * image[i - 1][width - 1].rgbtBlue) +
                                 image[i + 1][width - 2].rgbtBlue - image[i - 1][width - 2].rgbtBlue;

        bufferRx[i][width - 1] = (-2 * image[i][width - 2].rgbtRed) - image[i + 1][width - 2].rgbtRed -
                                 image[i - 1][width - 2].rgbtRed;
        bufferGx[i][width - 1] = (-2 * image[i][width - 2].rgbtGreen) - image[i + 1][width - 2].rgbtGreen -
                                 image[i - 1][width - 2].rgbtGreen;
        bufferBx[i][width - 1] = (-2 * image[i][width - 2].rgbtBlue) - image[i + 1][width - 2].rgbtBlue -
                                 image[i - 1][width - 2].rgbtBlue;
    }


    // loop for Gx values
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            // RED x buffer
            bufferRx[i][j] = (negative * image[i - 1][j - 1].rgbtRed) + 1 * (image[i - 1][j + 1].rgbtRed) +
                             (negative * 2 * image[i][j - 1].rgbtRed) + (2 * image[i][j + 1].rgbtRed) +
                             (negative * image[i + 1][j - 1].rgbtRed) + (1 * image[i + 1][j + 1].rgbtRed);

            // GREEN x buffer
            bufferGx[i][j] = (negative * image[i - 1][j - 1].rgbtGreen) + 1 * (image[i - 1][j + 1].rgbtGreen) +
                             (negative * 2 * image[i][j - 1].rgbtGreen) + (2 * image[i][j + 1].rgbtGreen) +
                             (negative * image[i + 1][j - 1].rgbtGreen) + (1 * image[i + 1][j + 1].rgbtGreen);

            // BLUE x buffer
            bufferBx[i][j] = (negative * image[i - 1][j - 1].rgbtBlue) + 1 * (image[i - 1][j + 1].rgbtBlue) +
                             (negative * 2 * image[i][j - 1].rgbtBlue) + (2 * image[i][j + 1].rgbtBlue) +
                             (negative * image[i + 1][j - 1].rgbtBlue) + (1 * image[i + 1][j + 1].rgbtBlue);

            // RED y buffer
            bufferRy[i][j] = (negative * image[i - 1][j - 1].rgbtRed) + (negative * 2 * image[i - 1][j].rgbtRed) +
                             (negative * image[i - 1][j + 1].rgbtRed) + (1 * image[i + 1][j - 1].rgbtRed) +
                             (2 * image[i + 1][j].rgbtRed) + (1 * image[i + 1][j + 1].rgbtRed);

            // GREEN y buffer
            bufferGy[i][j] = (negative * image[i - 1][j - 1].rgbtGreen) + (negative * 2 * image[i - 1][j].rgbtGreen) +
                             (negative * image[i - 1][j + 1].rgbtGreen) + (1 * image[i + 1][j - 1].rgbtGreen) +
                             (2 * image[i + 1][j].rgbtGreen) + (1 * image[i + 1][j + 1].rgbtGreen);

            // BLUE y buffer
            bufferBy[i][j] = (negative * image[i - 1][j - 1].rgbtBlue) + (negative * 2 * image[i - 1][j].rgbtBlue) +
                             (negative * image[i - 1][j + 1].rgbtBlue) + (1 * image[i + 1][j - 1].rgbtBlue) +
                             (2 * image[i + 1][j].rgbtBlue) + (1 * image[i + 1][j + 1].rgbtBlue);
        }
    }

    // capping all values to 255
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (bufferRx[i][j] > 255)
            {
                bufferRx[i][j] = 255;
            }
            if (bufferGx[i][j] > 255)
            {
                bufferGx[i][j] = 255;
            }
            if (bufferBx[i][j] > 255)
            {
                bufferBx[i][j] = 255;
            }
            if (bufferRy[i][j] > 255)
            {
                bufferRy[i][j] = 255;
            }
            if (bufferGy[i][j] > 255)
            {
                bufferGy[i][j] = 255;
            }
            if (bufferBy[i][j] > 255)
            {
                bufferBy[i][j] = 255;
            }
        }
    }

    // loop for output values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            bufferRx[i][j] = (int) round(sqrt(pow(bufferRx[i][j], 2) + pow(bufferRy[i][j], 2)));
            bufferGx[i][j] = (int) round(sqrt(pow(bufferGx[i][j], 2) + pow(bufferGy[i][j], 2)));
            bufferBx[i][j] = (int) round(sqrt(pow(bufferBx[i][j], 2) + pow(bufferBy[i][j], 2)));

            if (bufferRx[i][j] > 255)
            {
                bufferRx[i][j] = 255;
            }
            if (bufferGx[i][j] > 255)
            {
                bufferGx[i][j] = 255;
            }
            if (bufferBx[i][j] > 255)
            {
                bufferBx[i][j] = 255;
            }

            image[i][j].rgbtRed = (BYTE) bufferRx[i][j];
            image[i][j].rgbtGreen = (BYTE) bufferGx[i][j];
            image[i][j].rgbtBlue = (BYTE) bufferBx[i][j];

        }
    }
}
