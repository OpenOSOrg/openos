override CFLAGS :=  -Werror -Wall -std=gnu99 -O0 -g $(CFLAGS) -I.
CC = gcc

prog = testfork testforkexec


all: $(prog)

doforke.o: doforke.c doforke.h
testforkexec: testforkexec.c doforke.o doforke.h


.PHONY: clean 

clean:
	rm -f *.o *~ $(prog)
