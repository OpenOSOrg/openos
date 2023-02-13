override CFLAGS :=  -Werror -Wall -std=gnu99 -O0 -g $(CFLAGS) -I..
override LDFLAGS :=  -pthread

CC = gcc

test_files = test_get test_thrd
exec_files = ./test_get ./test_thrd

all: $(test_files)


.PHONY: checkprog
checkprog: $(test_files)

# Run the test programs                                                                                            
check: checkprog
	./run_tests.sh $(exec_files)


test_get.o : test_get.c ../philops.h
test_get: test_get.o ../philops.o 
test_thrd.o : test_thrd.c ../philops.h
test_thrd: test_thrd.o ../philops.o 

.PHONY: clean all

clean:
	rm -f *.o *~ $(prog)
