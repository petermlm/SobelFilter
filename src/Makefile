FILES=main.c sobel.c file_operations.c
OBJS=$(FILES:.c=.o)
ARQUIVE=libsobel.a
EXE=sobel
FLAGS=-std=c99 -g -lm

all: $(OBJS) archive
	gcc $(OBJS) -o $(EXE) $(FLAGS)

.c.o:
	gcc -c $< -o $@ $(FLAGS)

archive:
	ar rcs $(ARQUIVE) $(OBJS)

clean:
	rm $(OBJS) $(ARQUIVE) $(EXE)

