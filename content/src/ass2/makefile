override CFLAGS :=  -Werror -Wall -std=gnu99 -O0 -g $(CFLAGS) -I.
CC = gcc

prog = jmp1 jmp2 jmp3 jmp4 sched_simple
c_files = jmp1.c jmp2.c jmp3.c jmp4.c sched_simple.o
h_files = ec440threads.h 


all: $(prog)

jmp1 : jmp1.o ec440threads.h 
jmp2 : jmp2.o ec440threads.h 
jmp3 : jmp3.o ec440threads.h 
jmp4 : jmp4.o ec440threads.h 
sched_simple : sched_simple.o

.PHONY: clean 

clean:
	rm -f *.o *~ $(prog)
