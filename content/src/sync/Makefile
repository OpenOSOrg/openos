CC = gcc 
CFLAGS = -O2 -Wall -Wno-unused-result
LDFLAGS = -lpthread

prog = output_example bank_deposit counter counter_mutex counter_spinlock

all: $(prog) 

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)
    
counter.s: counter.c
	$(CC) -S $(CFLAGS) $<
    

#.PHONY: clean 

clean:
	rm -f *.o *~ $(prog)
