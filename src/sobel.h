#ifndef SOBEL_H
#define SOBEL_H

#include "macros.h"

int  rgbToGray   (byte *rgb, byte **gray, int buffer_size);
void makeOpMem   (byte *buffer, int buffer_size, int width, int cindex, byte *op_mem);
int  convolution (byte *X, int *Y, int c_size);
void itConv      (byte *buffer, int buffer_size, int width, int *op, byte **res);
void contour     (byte *sobel_h, byte *sobel_v, int gray_size, byte **contour_img);
int  sobelFilter (byte *rgb, byte **gray, byte **sobel_h_res, byte **sobel_v_res, byte **contour_img, int width, int height);

#endif

