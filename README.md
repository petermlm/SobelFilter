An implementation of the Sobel operator for edge detection in images. Below there is an example of taking the first image and having the calculated image bellow.

<img src="readme_imgs/imgin.png" alt="imgin" style="width: 200px;"/>
<img src="readme_imgs/imgout.png" alt="imgout" style="width: 200px;"/>

Arguments
=========

    sobel file_in file_out [-i file_h_out file_v_out] [-g file_gray] [-s 123x456]

**-i** - Generate intermediate files with the result of the vertical and horizontal operators.

**-g** - Generate the gray scale file.

**-s** - Size of image. Seperated by 'x'.

