all:
	cd src && make
	cd tests && make

check:
	cd tests && make check

run:
	convert imgs/img.png imgs/img.rgb
	./src/sobel imgs/img.rgb imgs/img_out.gray 512x512 -g imgs/img_out_gray.gray -i imgs/img_out_h.gray imgs/img_out_v.gray
	convert -size 512x512 -depth 8 imgs/img_out.gray imgs/img_out.png
	convert -size 512x512 -depth 8 imgs/img_out_gray.gray imgs/img_out_gray.png
	convert -size 512x512 -depth 8 imgs/img_out_h.gray imgs/img_out_h.png
	convert -size 512x512 -depth 8 imgs/img_out_v.gray imgs/img_out_v.png

clean:
	cd src && make clean
	cd tests && make clean

clean_run:
	rm imgs/img_out* imgs/img.rgb

