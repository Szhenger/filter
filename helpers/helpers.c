#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE avg_RGB = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed + 1) / 3;

            image[i][j].rgbtBlue = avg_RGB;
            image[i][j].rgbtGreen = avg_RGB;
            image[i][j].rgbtRed = avg_RGB;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp0 = image[i][j];
            RGBTRIPLE temp1 = image[i][width - (j + 1)];

            image[i][j] = temp1;
            image[i][width - (j + 1)] = temp0;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int counter = 0;
            int sumBlue = 0;
            int sumGreen = 0;
            int sumRed = 0;

            for (int m = i - 1; m < i + 2; m++)
            {
                for (int n = j - 1; n < j + 2; n++)
                {
                    if (m >= 0 && m < height && n >= 0 && n < width)
                    {
                        sumBlue += image[m][n].rgbtBlue;
                        sumGreen += image[m][n].rgbtGreen;
                        sumRed += image[m][n].rgbtRed;
                        counter++;
                    }
                }
            }

            copy[i][j].rgbtBlue = round((float) sumBlue / counter);
            copy[i][j].rgbtGreen = round((float) sumGreen / counter);
            copy[i][j].rgbtRed = round((float) sumRed / counter);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumGxBlue = 0;
            int sumGyBlue = 0;
            int sumGxGreen = 0;
            int sumGyGreen = 0;
            int sumGxRed = 0;
            int sumGyRed = 0;

            for (int m = 0; m < 3; m++)
            {
                for (int n = 0; n < 3; n++)
                {
                    if ((m + (i - 1)) >= 0 && (m + (i - 1)) < height && (n + (j - 1)) >= 0 && (n + (j - 1)) < width)
                    {
                        sumGxBlue += (Gx[m][n] * image[m + (i - 1)][n + (j - 1)].rgbtBlue);
                        sumGyBlue += (Gy[m][n] * image[m + (i - 1)][n + (j - 1)].rgbtBlue);
                        sumGxGreen += (Gx[m][n] * image[m + (i - 1)][n + (j - 1)].rgbtGreen);
                        sumGyGreen += (Gy[m][n] * image[m + (i - 1)][n + (j - 1)].rgbtGreen);
                        sumGxRed += (Gx[m][n] * image[m + (i - 1)][n + (j - 1)].rgbtRed);
                        sumGyRed += (Gy[m][n] * image[m + (i - 1)][n + (j - 1)].rgbtRed);
                    }
                }
            }

            int edgeBlue = round(sqrt(pow(sumGxBlue, 2) + pow(sumGyBlue, 2)));
            int edgeGreen = round(sqrt(pow(sumGxGreen, 2) + pow(sumGyGreen, 2)));
            int edgeRed = round(sqrt(pow(sumGxRed, 2) + pow(sumGyRed, 2)));

            if (edgeBlue < 255)
            {
                copy[i][j].rgbtBlue = edgeBlue;
            }
            else
            {
                copy[i][j].rgbtBlue = 255;
            }
            if (edgeGreen < 255)
            {
                copy[i][j].rgbtGreen = edgeGreen;
            }
            else
            {
                copy[i][j].rgbtGreen = 255;
            }
            if (edgeRed < 255)
            {
                copy[i][j].rgbtRed = edgeRed;
            }
            else
            {
                copy[i][j].rgbtRed = 255;
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
    return;
}
