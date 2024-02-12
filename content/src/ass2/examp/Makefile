override CFLAGS :=  -Werror -Wall -std=gnu99 -O0 -g $(CFLAGS) -I../provided/
CC = gcc

prog = jmp1 jmp2 jmp3 jmp4 calling_code
c_files = jmp1.c jmp2.c jmp3.c jmp4.c 
h_files = ec440threads.h 


all: $(prog)

.PHONY: clean 

clean:
	rm -f *.o *~ $(prog)
