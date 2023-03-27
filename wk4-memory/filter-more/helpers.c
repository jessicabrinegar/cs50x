#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for (int x= 0; x < width; x++)
        {
            // Convert pixels to floats
            float Red = image[i][x].rgbtRed;
            float Green = image[i][x].rgbtGreen;
            float Blue = image[i][x].rgbtBlue;
            int average = round((Red + Green + Blue) / 3);
            image[i][x].rgbtBlue = average;
            image[i][x].rgbtGreen = average;
            image[i][x].rgbtRed = average;

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
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create temporary image to store blurred pixels in
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Keep track of totals for each color value
            int totalRed = 0;
            int totalGreen = 0;
            int totalBlue = 0;
            // Count number of neighboring pixels
            float counter = 0.00;
            for (int y = -1; y < 2; y++)
            {
                for (int x = -1; x < 2; x++)
                {
                    int currentX = j + x;
                    int currentY = i + y;

                    // Check if the pixel is valid. If not, go to next loop iteration
                    if (currentX < 0 || currentY < 0 || currentX > height -1 || currentY > width -1)
                    {
                        continue;
                    }

                    totalRed += image[currentY][currentX].rgbtRed;
                    totalBlue += image[currentY][currentX].rgbtBlue;
                    totalGreen += image[currentY][currentX].rgbtGreen;

                    counter++;
                }
            }
            temp[i][j].rgbtRed = round(totalRed / counter);
            temp[i][j].rgbtBlue = round(totalBlue / counter);
            temp[i][j].rgbtGreen = round(totalGreen / counter);
        }
    }
    // Copy values of temp image into original image;
    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create temporary image to store transformed pixels in
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Initialize a 2-D array for Gx & Gy
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Loop through each row & column
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int redX = 0;
            int greenX = 0;
            int blueX = 0;
            int redY = 0;
            int greenY = 0;
            int blueY = 0;

            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    if (i - 1 + x < 0 || j - 1 + y < 0 || i - 1 + x  > height -1 || j - 1 + y > width -1)
                    {
                        continue;
                    }
                    // Calculate Gy
                    redX += image[i - 1 + x][j - 1 + y].rgbtRed * Gx[x][y];
                    greenX += image[i - 1 + x][j - 1 + y].rgbtGreen * Gx[x][y];
                    blueX += image[i - 1 + x][j - 1 + y].rgbtBlue * Gx[x][y];
                    redY += image[i - 1 + x][j - 1 + y].rgbtRed * Gy[x][y];
                    greenY += image[i - 1 + x][j - 1 + y].rgbtGreen * Gy[x][y];
                    blueY += image[i - 1 + x][j - 1 + y].rgbtBlue * Gy[x][y];
                }
            }
            // Calculate square roots
            int red = round(sqrt((redX * redX) + (redY * redY)));
            int blue = round(sqrt((blueX * blueX) + (blueY * blueY)));
            int green = round(sqrt((greenX * greenX) + (greenY * greenY)));
            // Cap at 255
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
            temp[i][j].rgbtRed = red;
            temp[i][j].rgbtBlue = blue;
            temp[i][j].rgbtGreen = green;
        }
    }
    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
        }
    }

    return;
}