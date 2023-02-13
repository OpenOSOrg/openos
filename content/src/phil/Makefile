override CFLAGS := -Wall -Werror -std=gnu99 -O0 -g $(CFLAGS) -I.
override LDFLAGS :=  -pthread
CC = gcc

prog = dining_phil

all: $(prog) 

# Automatically discover all test files
test_c_files=$(shell find tests -type f -name '*.c')
test_o_files=$(test_c_files:.c=.o)
test_files=$(test_c_files:.c=)

# The intermediate test .o files shouldn't be auto-deleted in test runs; they
# may be useful for incremental builds while fixing fs.c bugs.
.SECONDARY: $(test_o_files)

.PHONY: clean check checkprogs

# Rules to build each individual test
tests/%: tests/%.o philops.o
	$(CC) $(LDFLAGS) $+ $(LOADLIBES) $(LDLIBS) -o $@

# Build all of the test programs
checkprogs: $(test_files)

dining_phil.o : dining_phil.c philops.h
philops.o : philops.c philops.h
dining_phil: dining_phil.o philops.o


# Run the test programs
check: checkprogs
	tests/run_tests.sh $(test_files)

clean:
	rm -f *.o $(test_files) $(test_o_files) *~ tests/*~ $(prog)
