#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/**
 * This method takes the RGB value of a pixel and converts it to other values 
 * These values represent the grayscale version of an image? a YCbCr pixel 
 * 
 * Remember that it doesn't need to be returned. 
 * PASS BY REFERENCE 
 * 
 * rgb_pixels is for the colored pixels, ycc_pixels is for the grayscale
 */

/**
 * 1d arr rgb_pixels is passed by reference - it's width * height pixels in row major order (each pixel has 3 bytes)
 * output is passed in the ycc_pixels array (same dimensions) 
 * 
 * input arrays are properly sized, but there could be 0 values (width or height of 0)
 * in this case return an array of 0s
 */

/**
 * note that this is simply a kernel, so it's being called by the python program 
 */
void convert_to_YCrCb(unsigned char *rgb_pixels, unsigned char *ycc_pixels, int width, int height) {
    
    int i;
    int total_size = width*height*3;

    // these are 1d arrays, so they can't be accessed like arr[i][j]
    // when an image is read, what will be the arrangement of the pixels in the array 
    if (width==0||height==0) {
        // for (i = 0; i<width; i++) {
        //         ycc_pixels[i] = 0; 
        // }
        return;
    }

    for (i=0; i<(width*height*3); i+=3) {
        unsigned char r, g, b;
        r = rgb_pixels[i];
        g = rgb_pixels[i+1];
        b = rgb_pixels[i+2]; 

        char y = (char) round(0.299 * r + 0.587 * g + 0.114 * b);
        char cb = (char) round(128 - 0.168736 * r - 0.331264 * g + 0.5 * b);
        char cr = (char) round(128 + 0.5 * r - 0.418688 * g - 0.081312 * b); 

        ycc_pixels[i] = y; 
        ycc_pixels[i+1] = cb; 
        ycc_pixels[i+2]=cr;

    }

}

int main(int argc, char* argv[]) {
    
    return 0;
}