override CFLAGS :=  -Werror -Wall -std=gnu99 -O0 -g $(CFLAGS) -I.
CC = gcc

# simplefork - simple fork to show gdb
prog = simplefork wo zombie forkoff wo-static

all: $(prog)

wo-static: wo.c
	gcc -static  wo.c   -o wo-static

.PHONY: clean 

clean:
	rm -f *.o *~ $(prog)
