/* For illustration purposes only. 
 * This code is not complete and cannot be compiled into an executable.
 */
#include <stdatomic.h>
#include <stdbool.h>
#include "waitqueue.h"

extern char produce_item();
extern void consume_item(char item);

#define N 2

struct bounded_buffer {
	char data[N];   /* 'items' in this example are just bytes */
	int in;     /* index where producer inserts items, initially 0 */
	int out;    /* index where consumer removes items, initially 0 */
	atomic_int count;  /* number of items currently in buffer, initially 0 */
	struct wait_queue waitq; /* keep track of waiting threads */
};

struct bounded_buffer bb;

void *producer(void *arg) {
    while(true) {
        char item = produce_item();
        if (bb.count == N)
            sleep(&bb.waitq);
        bb.data[bb.in] = item;
        bb.in = (bb.in + 1) % N;
        bb.count++;
        if (bb.count == 1) 
            wakeup(&bb.waitq);
    }
}

void *consumer(void *arg) {
    while(true) {
        if (bb.count == 0) 
            sleep(&bb.waitq);
        char item = bb.data[bb.out];
        bb.out = (bb.out + 1) % N;
        bb.count--;
        if (bb.count == N-1) 
            wakeup(&bb.waitq);
        consume_item(item);
    }
}