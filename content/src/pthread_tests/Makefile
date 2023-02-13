override CFLAGS := -Wall -Werror -std=gnu99 -O0 -g $(CFLAGS) -I.
override LDFLAGS +=  -pthread
CC = gcc

prog = test_pthread_create test_pthread_barrier_basic test_mutex_basic test_mutex_parallel test_recur_mutex

all: $(prog) 

test_pthread_create: test_pthread_create.o
test_pthread_barrier_basic  : test_pthread_barrier_basic.o
test_mutex_basic: test_mutex_basic.o
test_mutex_parallel: test_mutex_parallel.o
test_recur_mutex: test_recur_mutex.o

# Run the test programs
check: 
	./run_tests.sh $(prog)

clean:
	rm -f *.o $(prog) *.o *~

