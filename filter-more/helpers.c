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
    // this is a much simpler approach, i will make an array bigger than the old one,
    // copy the input image to it, then do changes to input array based on the bigger copy
    // the copy will be an exact copy of the input array, but with a black one pixel border around the entire image
#define negative (-1)
//int counter = 0;
double Redx, Redy, Greenx, Greeny, Bluex, Bluey;

    RGBTRIPLE copy[height + 2][width + 2];
    memset(&copy[0][0], 0, sizeof(RGBTRIPLE) * (height + 2) * (width + 2));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //counter++;
            copy[i + 1][j + 1] = image[i][j];
        }
    }


    //printf("pixels copied: %d\n", counter);
    //counter = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //counter++;
            // RED x buffer
            Redx = (negative * copy[i][j].rgbtRed) + 1 * (copy[i][j + 2].rgbtRed) +
                             (negative * 2 * copy[i + 1][j].rgbtRed) + (2 * copy[i + 1][j + 2].rgbtRed) +
                             (negative * copy[i + 2][j].rgbtRed) + (1 * copy[i + 2][j + 2].rgbtRed);

            // GREEN x buffer
            Greenx = (negative * copy[i][j].rgbtGreen) + 1 * (copy[i][j + 2].rgbtGreen) +
                             (negative * 2 * copy[i + 1][j].rgbtGreen) + (2 * copy[i + 1][j + 2].rgbtGreen) +
                             (negative * copy[i + 2][j].rgbtGreen) + (1 * copy[i + 2][j + 2].rgbtGreen);

            // BLUE x buffer
            Bluex = (negative * copy[i][j].rgbtBlue) + 1 * (copy[i][j + 2].rgbtBlue) +
                             (negative * 2 * copy[i + 1][j].rgbtBlue) + (2 * copy[i + 1][j + 2].rgbtBlue) +
                             (negative * copy[i + 2][j].rgbtBlue) + (1 * copy[i + 2][j + 2].rgbtBlue);

            // RED y buffer
            Redy = (negative * copy[i][j].rgbtRed) + (negative * 2 * copy[i][j + 1].rgbtRed) +
                   (negative * copy[i][j + 2].rgbtRed) + (1 * copy[i + 2][j].rgbtRed) +
                   (2 * copy[i + 2][j + 1].rgbtRed) + (1 * copy[i + 2][j + 2].rgbtRed);

            // GREEN y buffer
            Greeny = (negative * copy[i][j].rgbtGreen) + (negative * 2 * copy[i][j + 1].rgbtGreen) +
                     (negative * copy[i][j + 2].rgbtGreen) + (1 * copy[i + 2][j].rgbtGreen) +
                     (2 * copy[i + 2][j + 1].rgbtGreen) + (1 * copy[i + 2][j + 2].rgbtGreen);

            // BLUE y buffer
            Bluey = (negative * copy[i][j].rgbtBlue) + (negative * 2 * copy[i][j + 1].rgbtBlue) +
                    (negative * copy[i][j + 2].rgbtBlue) + (1 * copy[i + 2][j].rgbtBlue) +
                    (2 * copy[i + 2][j + 1].rgbtBlue) + (1 * copy[i + 2][j + 2].rgbtBlue);

            // cap Gx and Gy values to 255
            if (Redx > 255)
            {
                Redx = 255;
            }
            if (Greenx > 255)
            {
                Greenx = 255;
            }
            if (Bluex > 255)
            {
                Bluex = 255;
            }
            if (Redy > 255)
            {
                Redy = 255;
            }
            if (Greeny > 255)
            {
                Greeny = 255;
            }
            if (Bluey > 255)
            {
                Bluey = 255;
            }

            // calculate equivalent pixel based on Gx and Gy values
            Redx = (int) round(sqrt(pow(Redx, 2) + pow(Redy, 2)));
            Greenx = (int) round(sqrt(pow(Greenx, 2) + pow(Greeny, 2)));
            Bluex = (int) round(sqrt(pow(Bluex, 2) + pow(Bluey, 2)));

            // cap at 255 again
            if (Redx > 255)
                Redx = 255;
            if (Greenx > 255)
                Greenx = 255;
            if (Bluex > 255)
                Bluex = 255;

            // copy the pixel to original image
            image[i][j].rgbtRed = (BYTE) Redx;
            image[i][j].rgbtGreen = (BYTE) Greenx;
            image[i][j].rgbtBlue = (BYTE) Bluex;
        }
    }
}
