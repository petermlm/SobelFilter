all:
	cd src && make
	cd tests && make

check:
	cd tests && make check

run:
	echo "TODO"

clean:
	cd src && make clean
	cd tests && make clean

clean_run:
	rm imgs/img.rgb imgs/img_out_pre.gray imgs/img_out_pre.png imgs/img_out.gray imgs/img_out.png imgs/img_out_h.gray imgs/img_out_h.png imgs/img_out_v.gray imgs/img_out_v.png

