override CFLAGS :=  -Werror -Wall -std=gnu99 -O0 -g $(CFLAGS) -I.
CC = gcc

prog = fcopy fcopy2

all: $(prog)

.PHONY: clean 

clean:
	rm -f *.o *~ $(prog)
