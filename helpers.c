#include "helpers.h"
#include <math.h>
#include <cs50.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Obtain values of each colour in current pixel

            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            // Calculate average of blue green and red in current pixel

            int average = round((red + green + blue) / 3.0);

            // Implement average across all three colours in current pixel

            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally

void swap(RGBTRIPLE *pixela, RGBTRIPLE *pixelb);

// Iterate over half of each row and swap pixels

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            swap(&image[i][j], &image[i][width - 1 - j]);
        }
    }
    return;
}

// Function definition for swapping pixels

void swap(RGBTRIPLE *pixela, RGBTRIPLE *pixelb)
{
    RGBTRIPLE temp = *pixela;
    *pixela = *pixelb;
    *pixelb = temp;
}

// Blur image

bool valid_pixel(int i, int j, int height, int width);

RGBTRIPLE get_blurred_pixel(int i, int j, int height, int width, RGBTRIPLE image[height][width]);

// Main function for blurring image

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Copy each blurred pixel into new image 2D array

            new_image[i][j] = get_blurred_pixel(i, j, height, width, image);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Copy new blurred image into original image 2D array

            image[i][j] = new_image[i][j];
        }
    }
    return;
}

// Function definition for checking if current pixel is valid (i.e whether we've reached the edge of the image 2D array)

bool valid_pixel(int i, int j, int height, int width)
{
    if ((i >= 0 && i < height) && (j >= 0 && j < width))
    {
        return 0;
    }
    return 1;
}

// Function definition for obtaining blurred pixels

RGBTRIPLE get_blurred_pixel(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    int red = 0;
    int green = 0;
    int blue = 0;
    int num_valid_pixels = 0;

    // Nested loop to iterate around all surrounding pixels of current pixel

    for (int di = -1; di <= 1; di++)
    {
        for (int dj = -1; dj <= 1; dj++)
        {
            // Obtain new pixel position (row i and column j)

            int new_i = i + di;
            int new_j = j + dj;
            if (valid_pixel(new_i, new_j, height, width) == 0)
            {
                // Keep track of number of valid pixels around current pixel
                num_valid_pixels++;
                // Add red values for all surrounding pixels together
                red += image[new_i][new_j].rgbtRed;
                // Add green values for all surrounding pixels together
                green += image[new_i][new_j].rgbtGreen;
                // Add blue values for all surrounding pixels together
                blue += image[new_i][new_j].rgbtBlue;
            }
        }
    }
    // Declare new blurred pixel RGBTRIPLE struct
    RGBTRIPLE blurred_pixel;
    // Obtain average of red values for all surrounding pixels
    blurred_pixel.rgbtRed = round((float) red / num_valid_pixels);
    // Obtain average of green values for all surrounding pixels
    blurred_pixel.rgbtGreen = round((float) green / num_valid_pixels);
    // Obtain average of blue values for all surrounding pixels
    blurred_pixel.rgbtBlue = round((float) blue / num_valid_pixels);
    // Function return overall blurred pixel RBGTRIPLE struct
    return blurred_pixel;
}

// Detect edges

// Prototype function to check if current pixel is valid (i.e whether we've reached the edge of the image 2D array)

bool valid_pixel(int i, int j, int height, int width);

// Prototype function to cap Sobel filter value at 255

int cap(int n);

// Obtain Sobel filter pixel

RGBTRIPLE get_Sobel_pixel(int i, int j, int height, int width, RGBTRIPLE image[height][width]);

void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE Sobel_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Copy each blurred pixel into new image 2D array

            Sobel_image[i][j] = get_Sobel_pixel(i, j, height, width, image);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Copy new edged image into original image 2D array

            image[i][j] = Sobel_image[i][j];
        }
    }
    return;
}

// Function definition to cap Sobel filter value at 255

int cap(int n)
{
    if (n > 255)
    {
        n = 255;
    }
    return n;
}

// Function definition to calculate Gx and Gy value for each pixel

RGBTRIPLE get_Sobel_pixel(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 
    2}, {-1, 0, 1}};
    int Gy[3][3] = {{ -1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int redGx = 0;
    int greenGx = 0;
    int blueGx = 0;
    int redGy = 0;
    int greenGy = 0;
    int blueGy = 0;

// Nested loop to iterate around all surrounding pixels of current pixel

    for (int di = -1; di <= 1; di++)
    {
        for (int dj = -1; dj <= 1; dj++)
        {
            int new_i = i + di;
            int new_j = j + dj;
            if (valid_pixel(new_i, new_j, height, width) == 0)
            {
                // Calculate Gx for each colour in current pixel
                redGx += Gx[di + 1][dj + 1] * image[new_i][new_j].rgbtRed;
                greenGx += Gx[di + 1][dj + 1] * image[new_i][new_j].rgbtGreen;
                blueGx += Gx[di + 1][dj + 1] * image[new_i][new_j].rgbtBlue;

                // Calculate Gy for each colour in current pixel
                redGy += Gy[di + 1][dj + 1] * image[new_i][new_j].rgbtRed;
                greenGy += Gy[di + 1][dj + 1] * image[new_i][new_j].rgbtGreen;
                blueGy += Gy[di + 1][dj + 1] * image[new_i][new_j].rgbtBlue;
            }
        }
    }
    // Declare new Sobel pixel RGBTRIPLE struct
    RGBTRIPLE Sobel_pixel;
    // Calculate Sobel Filter for each colour
    Sobel_pixel.rgbtRed = cap(round(sqrt((redGx * redGx) + (redGy * redGy))));
    Sobel_pixel.rgbtGreen = cap(round(sqrt((greenGx * greenGx) + (greenGy * greenGy))));
    Sobel_pixel.rgbtBlue = cap(round(sqrt((blueGx * blueGx) + (blueGy * blueGy))));

    return Sobel_pixel;
}

