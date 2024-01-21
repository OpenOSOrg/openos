override CFLAGS :=  -Werror -Wall -std=gnu99 -O0 -g $(CFLAGS) -I.
CC = gcc

prog = testfork testforkexec pipe wo


all: $(prog)

check: $(prog)
	chmod +x run_tests.sh
	./run_tests.sh $(prog)

doforke.o: doforke.c doforke.h
testforkexec: testforkexec.c doforke.o doforke.h
wo: wo.c
	gcc -static  wo.c -o wo

.PHONY: clean 

clean:
	rm -f *.o *~ $(prog)
