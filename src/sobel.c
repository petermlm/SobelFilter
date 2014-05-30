#include "sobel.h"

#include <stdlib.h>
#include <math.h>

#include "macros.h"

/*
 * Transforms the rgb information of an image stored in buffer to it's gray
 * representation
 */

int rgbToGray(byte *rgb, byte **gray, int buffer_size) {
    // Take size for gray image and allocate memory
    int gray_size = buffer_size / 3;
    *gray = malloc(sizeof(byte) * gray_size);

    // Make pointers for iteration
    byte *p_rgb = rgb;
    byte *p_gray = *gray;

    // Calculate the value for every pixel in gray
    for(int i=0; i<gray_size; i++) {
        *p_gray = 0.30*p_rgb[0] + 0.59*p_rgb[1] + 0.11*p_rgb[2];

        p_rgb += 3;
        p_gray++;
    }

    return gray_size;
}

/*
 * Make the operation memory for iterative convolution
 */

void makeOpMem(byte *buffer, int buffer_size, int cindex, byte *op_mem) {
    int width = sqrt(buffer_size);
    int line = cindex-width;
    int offset = -1;

    for(int i=0; i<SOBEL_OP_SIZE; i++) {
        int index = line + offset;

        if(index >= 0 && index < buffer_size) {
            op_mem[i] = buffer[index];
        } else {
            op_mem[i] = 0;
        }

        offset++;

        if((i+1) % 3 == 0) {
            line += width;
            offset = -1;
        }
    }
}

/*
 * Performs convolution between first two arguments
 */

int convolution(byte *X, int *Y, int c_size) {
    int sum = 0;

    for(int i=0; i<c_size; i++) {
        sum += X[i] * Y[c_size-i-1];
    }

    return sum;
}

/*
 * Iterate Convolution
 */

void itConv(byte *buffer, int buffer_size, int *op, byte **res) {
    // Allocate memory for result
    *res = malloc(sizeof(byte) * buffer_size);

    // Temporary memory for each pixel operation
    byte op_mem[SOBEL_OP_SIZE];

    // Make convolution for every pixel
    for(int i=0; i<buffer_size; i++) {
        // Make op_mem
        makeOpMem(buffer, buffer_size, i, op_mem);

        // Convolution
        (*res)[i] = (byte) (1.0/4.0 * abs(convolution(op_mem, op, SOBEL_OP_SIZE)));
    }
}

/*
 * Contour
 */

void contour(byte *sobel_h, byte *sobel_v, int gray_size, byte **contour_img) {
    // Allocate memory for contour_img
    *contour_img = malloc(sizeof(byte) * gray_size);

    // Iterate through every pixel to calculate the contour image
    for(int i=0; i<gray_size; i++) {
        (*contour_img)[i] = 255 - (1.0/2.0)*(sobel_h[i] + sobel_v[i]);
    }
}


