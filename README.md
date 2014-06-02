An implementation of the Sobel operator for edge detection in images. Below there is an example of taking the first image and having the calculated image bellow.

<img src="readme_imgs/imgin.png" alt="imgin" style="width: 200px;"/>
<img src="readme_imgs/imgout.png" alt="imgout" style="width: 200px;"/>

Arguments
=========

    sobel file_in file_out 123x456 [-i file_h_out file_v_out] [-g file_gray]

The *file_in* and *file_out* arguments are, obvious, the file for which the contour should be calculated and the file with that calculated contour, respectively. The third argument is the size of the image (width x height). It is needed because the RGB file type does not contain any meta information about the image it self.

The optional arguments are:

**-i** - Generate intermediate files with the result of the vertical and horizontal operators.

**-g** - Generate the gray scale file.

