# Filter-
This project involved implementing a program that applies various filters to bitmap (BMP) image files. This involved iterating over each pixel in the image and manipulating them in a particular way.

For example, the grayscale filter simply takes the average of the RGB values for each pixel, and sets them equal to this average. As all three hexadecimal values are equal, this results in varying shades of gray along the black-white spectrum. 

The blur filter involved using a 3x3 pixel "blur box" by setting the hexadecimal colour value of each pixel to be an average of the all the pixels immediately around it.

The edges filter uses a 3x3 pixel grid system similar to the blur filter, but instead of using a blur box, the Sobel operator is applied to each pixel. The Sobel operator uses two separate 3x3 grids or 'kernals' to calculate two weighted sums for each pixel, one for the x-direction and one for the y-direction. This detects any edges around each pixel in both directions. The result is the image shown on the left (or above for mobile users).
