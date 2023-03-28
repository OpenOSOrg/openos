CC = gcc

prog = output_example bank_deposit counter


all: $(prog)

output_example: output_example.c 
	$(CC) -o $@ $< -lpthread

bank_deposit: bank_deposit.c
	$(CC) -o $@ $< -lpthread

counter.s:counter.c
	$(CC) -S $<
    
counter: counter.s
	$(CC) -o $@ $< -lpthread

.PHONY: clean 

clean:
	rm -f *.o *~ $(prog)
