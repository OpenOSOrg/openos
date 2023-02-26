override CFLAGS :=  -Werror -Wall -std=gnu99 -O0 -g $(CFLAGS) -I.
CC = gcc

prog = fcopy fcopy2

fcopy : fcopy.c
	$(CC) -Werror -Wall  -O0 -g fcopy.c -o fcopy

all: $(prog)

.PHONY: clean 

clean:
	rm -f *.o *~ $(prog)
