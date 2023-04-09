/* For illustration purposes only. 
 * This code is not complete and cannot be compiled into an executable.
 */
#include <semaphore.h>
#include <stdbool.h>

extern char produce_item();
extern void consume_item(char item);

#define N 2

struct bounded_buffer {
	char data[N];   /* 'items' in this example are just bytes */
	int in;     /* index where producer inserts items, initially 0 */
	int out;    /* index where consumer removes items, initially 0 */
    sem_t sem_empty;
    sem_t sem_filled;
    sem_t sem_mutex;
};

struct bounded_buffer bb;

void *producer(void *arg) {
    while(true) {
        char item = produce_item();
        sem_wait(&bb.sem_empty);
        sem_wait(&bb.sem_mutex);
        bb.data[bb.in] = item;
        bb.in = (bb.in + 1) % N;
        sem_post(&bb.sem_mutex);
        sem_post(&bb.sem_filled);
    }
}

void *consumer(void *arg) {
    while(true) {
        sem_wait(&bb.sem_filled);
        sem_wait(&bb.sem_mutex);
        char item = bb.data[bb.out];
        bb.out = (bb.out + 1) % N;
        sem_post(&bb.sem_mutex);
        sem_post(&bb.sem_empty);
        consume_item(item);
    }
}

int main()
{
    sem_init(&bb.sem_empty, 0, N);
    sem_init(&bb.sem_filled, 0, 0);
    sem_init(&bb.sem_mutex, 0, 1);
    
    /*** Thread creation stuff here ***/
    
    return 0;
}