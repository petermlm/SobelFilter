#include "sobel.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    int bottom = cindex-width < 0;
    int top = cindex+width >= buffer_size;
    int left = cindex % width == 0;
    int right = (cindex+1) % width == 0;

    op_mem[0] = !bottom && !left  ? buffer[cindex-width-1] : 0;
    op_mem[1] = !bottom           ? buffer[cindex-width]   : 0;
    op_mem[2] = !bottom && !right ? buffer[cindex-width+1] : 0;

    op_mem[3] = !left             ? buffer[cindex-1]       : 0;
    op_mem[4] = buffer[cindex];
    op_mem[5] = !right            ? buffer[cindex+1]       : 0;

    op_mem[6] = !top && !left     ? buffer[cindex+width-1] : 0;
    op_mem[7] = !top              ? buffer[cindex+width]   : 0;
    op_mem[8] = !top && !right    ? buffer[cindex+width+1] : 0;
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
    memset(op_mem, 0, SOBEL_OP_SIZE);

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

int sobelFilter(byte *rgb, byte **gray, byte **sobel_h_res, byte **sobel_v_res, byte **contour_img, int rgb_size) {
    int sobel_h[] = {1, 0, -1, 2, 0, -2, 1, 0, -1},
        sobel_v[] = {1, 2, 1, 0, 0, 0, -1, -2, -1};

    // Get gray representation of the image
    int gray_size = rgbToGray(rgb, gray, rgb_size);

    // Make sobel operations
    itConv(*gray, gray_size, sobel_h, sobel_h_res);
    itConv(*gray, gray_size, sobel_v, sobel_v_res);

    // Calculate contour matrix
    contour(*sobel_h_res, *sobel_v_res, gray_size, contour_img);

    return gray_size;
}

