#include "helpers.h"
#include <math.h>

int Gx[3][3] = {
    {-1, 0, 1},
    {-2, 0, 2},
    {-1, 0, 1}};

int Gy[3][3] = {
    {-1, -2, -1},
    {0, 0, 0},
    {1, 2, 1}};

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate the average value of RGB channels
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Set RGB channels to the rounded average value
            image[i][j].rgbtRed = round(avg);
            image[i][j].rgbtGreen = round(avg);
            image[i][j].rgbtBlue = round(avg);
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create a temporary array to store the blurred image
    RGBTRIPLE blurred[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sumRed = 0, sumGreen = 0, sumBlue = 0;
            int count = 0;

            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int newI = i + di;
                    int newJ = j + dj;

                    // check if the pixel is within the image bounds
                    if (newI >= 0 && newI < height && newJ >= 0 && newJ < width)
                    {
                        sumRed += image[newI][newJ].rgbtRed;
                        sumGreen += image[newI][newJ].rgbtGreen;
                        sumBlue += image[newI][newJ].rgbtBlue;
                        count++;
                    }
                }
            }
            // calculate the average of the RGB values of the neighboring pixels
            blurred[i][j].rgbtRed = round(sumRed / count);
            blurred[i][j].rgbtGreen = round(sumGreen / count);
            blurred[i][j].rgbtBlue = round(sumBlue / count);
        }
    }

    // copy blurred image back to the image array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = blurred[i][j];
        }
    }
}

void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int gxRed, gxGreen, gxBlue, gyRed, gyGreen, gyBlue;
    float magnitudeRed, magnitudeGreen, magnitudeBlue;
    int threshold = 80;

    // Iterate over each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            gxRed = gyRed = gxGreen = gyGreen = gxBlue = gyBlue = 0;

            // Calculate the Gx and Gy values for each color channel
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    // Skip pixels outside the image boundaries
                    if (i + k < 0 || i + k >= height || j + l < 0 || j + l >= width)
                    {
                        continue;
                    }

                    gxRed += image[i + k][j + l].rgbtRed * Gx[k + 1][l + 1];
                    gxGreen += image[i + k][j + l].rgbtGreen * Gx[k + 1][l + 1];
                    gxBlue += image[i + k][j + l].rgbtBlue * Gx[k + 1][l + 1];

                    gyRed += image[i + k][j + l].rgbtRed * Gy[k + 1][l + 1];
                    gyGreen += image[i + k][j + l].rgbtGreen * Gy[k + 1][l + 1];
                    gyBlue += image[i + k][j + l].rgbtBlue * Gy[k + 1][l + 1];
                }
            }

            // Calculate the magnitude values
            magnitudeRed = sqrt(gxRed * gxRed + gyRed * gyRed);
            magnitudeGreen = sqrt(gxGreen * gxGreen + gyGreen * gyGreen);
            magnitudeBlue = sqrt(gxBlue * gxBlue + gyBlue * gyBlue);

            // Clamp the magnitude values to a maximum of 255
            magnitudeRed = (magnitudeRed > 255) ? 255 : magnitudeRed;
            magnitudeGreen = (magnitudeGreen > 255) ? 255 : magnitudeGreen;
            magnitudeBlue = (magnitudeBlue > 255) ? 255 : magnitudeBlue;

            // Set RGB values based on magnitude and threshold
            temp[i][j].rgbtRed = (magnitudeRed > threshold) ? 255 : (BYTE)magnitudeRed;
            temp[i][j].rgbtGreen = (magnitudeGreen > threshold) ? 255 : (BYTE)magnitudeGreen;
            temp[i][j].rgbtBlue = (magnitudeBlue > threshold) ? 255 : (BYTE)magnitudeBlue;
        }
    }

    // Copy the updated image back to the original image array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}