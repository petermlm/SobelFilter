#include <stdio.h>
#include <string.h>

#include "macros.h"
#include "sobel.h"
#include "file_operations.h"

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

