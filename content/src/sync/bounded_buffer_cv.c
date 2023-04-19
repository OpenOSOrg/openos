/* For illustration purposes only. 
 * This code is not complete and cannot be compiled into an executable.
 */
#include <pthread.h>
#include <stdbool.h>

extern char produce_item();
extern void consume_item(char item);

#define N 2

struct bounded_buffer {
    char data[N];   /* 'items' in this example are just bytes */
    int in;     /* index where producer inserts items, initially 0 */
    int out;    /* index where consumer removes items, initially 0 */
    int count;
    pthread_mutex_t buflock;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;
};

struct bounded_buffer bb;

void *producer(void *arg) {
    while(true) {
        char item = produce_item();
        pthread_mutex_lock(&bb.buflock);
        while(bb.count == N) {
            pthread_cond_wait(&bb.notfull, &bb.buflock);
        }
        bb.data[bb.in] = item;
        bb.in = (bb.in + 1) % N;
        bb.count++;
        pthread_cond_signal(&bb.notempty);
        pthread_mutex_unlock(&bb.buflock);
    }
}

void *consumer(void *arg) {
    while(true) {
        pthread_mutex_lock(&bb.buflock);
        while (bb.count == 0) {
            pthread_cond_wait(&bb.notempty, &bb.buflock);
        }
        char item = bb.data[bb.out];
        bb.out = (bb.out + 1) % N;
        bb.count--;
        pthread_cond_signal(&bb.notfull);
        pthread_mutex_unlock(&bb.buflock);

        consume_item(item);
    }
}

int main()
{
    pthread_mutex_init(&bb.buflock, NULL);
    pthread_cond_init(&bb.notfull, NULL);
    pthread_cond_init(&bb.notempty, NULL);
    
    /*** Thread creation stuff here ***/
    
    return 0;
}