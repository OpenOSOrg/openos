CC = gcc 
CFLAGS = -O2 -Wall -Wno-unused-result
LDFLAGS = -lpthread

prog = output_example bank_deposit counter counter_mutex counter_spinlock counter_ticketlock check_spinlock_fairness check_ticketlock_fairness check_mutex_fairness

all: $(prog) 

%: %.c spinlock.h ticketlock.h
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)
    
counter.s: counter.c
	$(CC) -S $(CFLAGS) $<
    

#.PHONY: clean 

clean:
	rm -f *.o *~ $(prog)
