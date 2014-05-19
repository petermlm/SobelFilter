FILES=main.c file_operations.c
EXE=sobel
FLAGS=-std=c99 -g -lm

all:
	gcc $(FILES) -o $(EXE) $(FLAGS)

run:
	convert img.png img.rgb
	./$(EXE)
	convert -size 512x512 -depth 8 img_out_pre.gray img_out_pre.png
	convert -size 512x512 -depth 8 img_out.gray img_out.png
	convert -size 512x512 -depth 8 img_out_h.gray img_out_h.png
	convert -size 512x512 -depth 8 img_out_v.gray img_out_v.png

clean:
	rm img.rgb img_out* $(EXE)

