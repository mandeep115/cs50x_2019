#include <stdio.h>
#include <math.h>
#include "string.h"
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            BYTE avg = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3;
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
            
            // image[i][j].rgbtRed = image[i][j].rgbtRed * 0.3;
            // image[i][j].rgbtGreen = image[i][j].rgbtGreen * 0.59;
            // image[i][j].rgbtBlue = image[i][j].rgbtBlue * 0.11;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;
            
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            image[i][j].rgbtRed = fmin(255, sepiaRed);
            image[i][j].rgbtGreen = fmin(255, sepiaGreen);
            image[i][j].rgbtBlue = fmin(255, sepiaBlue);
        }
    }
    return;
}

// Swap function was not working

// void swap(RGBTRIPLE *a, RGBTRIPLE *b) {
//     RGBTRIPLE temp = *a;
//     *a = *b;
//     *b = temp;
// }

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width / 2; j++) {
            //A buggy code makes image symetrical from center

            // image[i][j] = image[i][width - j];

            // swap(&image[i][j], &image[i][width - j]);

            temp = image[i][j];
            image[i][j] = image[i][width - j];
            image[i][width - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) {
    RGBTRIPLE temp[height][width];

    memcpy(temp, image, sizeof(RGBTRIPLE) * height * width);

  
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
                
            float avg = 0.0;

            int red = 0;    
            int green = 0;  
            int blue = 0; 
            for (int k = -1; k <= 1; k++){
                for (int l = -1; l <= 1; l++){
                    if(i + k != height &&
                        i + k != -1 &&
                        j + l != width &&
                        j + l != -1) {
                        red += temp[i+k][j+l].rgbtRed;
                        green += temp[i+k][j+l].rgbtGreen;
                        blue += temp[i+k][j+l].rgbtBlue;
                        avg++;
                    }
                }
            }
            image[i][j].rgbtRed = red/avg;
            image[i][j].rgbtGreen = green/avg;
            image[i][j].rgbtBlue = blue/avg;
        }
    }
    return;
}
