#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    char *file_in, *file_out, *file_out_h, *file_out_v, *file_gray;
    int inter_files = 0, gray_file = 0;
    byte *rgb, *gray;
    int rgb_size, gray_size;
    int sobel_h[] = {1, 0, -1, 2, 0, -2, 1, 0, -1},
        sobel_v[] = {1, 2, 1, 0, 0, 0, -1, -2, -1};
    byte *sobel_h_res, *sobel_v_res;
    byte *contour_img;

    // Get arguments
    if(argc < 3) {
        printf("Usage: TODO\n");
        return 1;
    }

    // File names
    file_in = argv[1];
    file_out = argv[2];

    // Get optional arguments
    int arg_index = 3;
    while(arg_index < argc) {
        // If there is a flag to create intermediate files
        if(strcmp(argv[arg_index], "-i") == 0) {
            if(arg_index+3 > argc) {
                printf("Usage: TODO\n");
                return 1;
            }

            inter_files = 1;
            file_out_h = argv[arg_index+1];
            file_out_v = argv[arg_index+2];

            arg_index += 3;
        }

        else if(strcmp(argv[arg_index], "-g") == 0) {
            if(arg_index+2 > argc) {
                printf("Usage: TODO\n");
                return 1;
            }

            gray_file = 1;
            file_gray = argv[arg_index+1];

            arg_index += 2;
        }

        else {
            printf("Argument \"%s\", is unknown.\n", argv[arg_index]);
            return 1;
        }
    }

    // Read file to rgb and get size
    rgb_size = readFile(file_in, &rgb);

    // Get gray representation of the image
    gray_size = rgbToGray(rgb, &gray, rgb_size);

    // Write gray image
    if(gray_file) {
        writeFile(file_gray, gray, gray_size);
    }

    // Make sobel operations
    itConv(gray, gray_size, sobel_h, &sobel_h_res);
    itConv(gray, gray_size, sobel_v, &sobel_v_res);

    // Write image after each sobel operator
    if(inter_files) {
        writeFile(file_out_h, sobel_h_res, gray_size);
        writeFile(file_out_v, sobel_v_res, gray_size);
    }

    // Calculate contour matrix
    contour(sobel_h_res, sobel_v_res, gray_size, &contour_img);

    // Write sobel img to a file
    writeFile(file_out, contour_img, gray_size);

    return 0;
}

