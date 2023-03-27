#include "bmp.h"

/*
if image represents the whole pic, then image[0] represents the first row,
and image[0][0] represents the pixel in the upper-left corner of the image
*/

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]);

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]);

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]);

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]);

