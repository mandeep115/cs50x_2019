#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include "string.h"
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]) {

    RGBTRIPLE temp[height][width];
    memcpy(temp, image, sizeof(RGBTRIPLE) * height * width);

    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int redx = 0, redy = 0;
            int greenx = 0, greeny = 0;
            int bluex = 0, bluey = 0;

            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    if (i - 1 + k < 0 || i - 1 + k > height - 1 || j - 1 + l < 0 || j - 1 + l > width - 1) {
                        continue;
                    }
                    redx = redx + (temp[i+k-1][j+l-1].rgbtRed * Gx[k][l]);
                    greenx = greenx + (temp[i+k-1][j+l-1].rgbtGreen * Gx[k][l]);
                    bluex = bluex + (temp[i+k-1][j+l-1].rgbtBlue * Gx[k][l]);
                    
                    redy = redy + (temp[i+k-1][j+l-1].rgbtRed * Gy[k][l]);
                    greeny = greeny + (temp[i+k-1][j+l-1].rgbtGreen * Gy[k][l]);
                    bluey = bluey + (temp[i+k-1][j+l-1].rgbtBlue * Gy[k][l]);
                }
            }

            int r = round(sqrt((redx * redx) + (redy * redy)));
            int g = round(sqrt((greenx * greenx) + (greeny * greeny)));
            int b = round(sqrt((bluex * bluex) + (bluey * bluey)));

            image[i][j].rgbtRed = fmin(255, r);
            image[i][j].rgbtGreen = fmin(255, g);
            image[i][j].rgbtBlue = fmin(255, b);

        }
    }
    return;
}
