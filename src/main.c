#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "macros.h"
#include "file_operations.h"

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

/*
 * Main function
 */

int main(int argc, char *argv[]) {
    byte *rgb, *gray;
    int rgb_size, gray_size;
    int sobel_h[] = {1, 0, -1, 2, 0, -2, 1, 0, -1},
        sobel_v[] = {1, 2, 1, 0, 0, 0, -1, -2, -1};
    byte *sobel_h_res, *sobel_v_res;
    byte *contour_img;

    // Read file to rgb and get size
    rgb_size = readFile("../imgs/img.rgb", &rgb);

    // Get gray representation of the image
    gray_size = rgbToGray(rgb, &gray, rgb_size);

    // Write gray image
    writeFile("../imgs/img_out_pre.gray", gray, gray_size);

    // Make sobel operations
    itConv(gray, gray_size, sobel_h, &sobel_h_res);
    itConv(gray, gray_size, sobel_v, &sobel_v_res);

    // Write image after each sobel operator
    writeFile("../imgs/img_out_h.gray", sobel_h_res, gray_size);
    writeFile("../imgs/img_out_v.gray", sobel_v_res, gray_size);

    // Calculate contour matrix
    contour(sobel_h_res, sobel_v_res, gray_size, &contour_img);

    // Write sobel_img to a file
    writeFile("../imgs/img_out.gray", contour_img, gray_size);

    return 0;
}

