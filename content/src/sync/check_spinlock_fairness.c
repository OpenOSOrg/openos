#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include "spinlock.h"

spinlock_t splock;
atomic_bool start;
atomic_bool done;

struct thread_info {
    pthread_t tid;
    unsigned iters_done;
};

static void *thread_func(void *arg)
{
    struct thread_info *my_info = (struct thread_info *)arg;
    unsigned i = 0;
    
    while(!start) {} ; /* Wait until parent flags that all threads have been created */ 
    
    while (!done) {
        spinlock_acquire(&splock);
        i++;
        spinlock_release(&splock);
    }

    my_info->iters_done = i;
    return (void *)0;
}



int main(int argc, char **argv)
{
    struct thread_info *tinfo;
    int duration;
    int nthreads, i;
    
    if (argc != 3) {
        fprintf(stderr,"Usage: %s <num_threads> <duration>\n\t where duration is the number of seconds for threads to run.\n",argv[0]);
        return 1;
    }

    start = false;
    done = false;
    nthreads = atoi(argv[1]);
    duration = atoi(argv[2]);
    spinlock_init( &splock );
    
    printf("Main thread: Beginning test with %d threads, running for %d seconds\n", nthreads, duration);
    
    tinfo = (struct thread_info *)calloc(nthreads, sizeof(struct thread_info));

    /* We create the requested number of threads, all doing the same work */
    for (i = 0; i < nthreads; i++) {
        (void)pthread_create(&tinfo[i].tid, NULL, thread_func, (void *)&tinfo[i] );
    }
    
    /* All threads created. Let them run concurrently for requested duration. */
    start = true;
    sleep(duration);
    done = true;
    
    /* Wait for child threads to finish */
    for (i = 0; i < nthreads; i++) {
        pthread_join(tinfo[i].tid, NULL);
    }

    unsigned min_iters = UINT_MAX;
    unsigned max_iters = 0; 
    unsigned tot_iters = 0;
    for (i = 0; i < nthreads; i++) {
        tot_iters += tinfo[i].iters_done;
        if (tinfo[i].iters_done < min_iters) {
            min_iters = tinfo[i].iters_done;
        }
        if (tinfo[i].iters_done > max_iters) {
            max_iters = tinfo[i].iters_done;
        }
        printf("Thread %d completed %u iters\n", i, tinfo[i].iters_done);
    }
    
    unsigned diff = max_iters - min_iters;
    printf("\nTOTAL: %u iterations completed.\n", tot_iters);
    printf("Unfairness: Most productive thread completed %u iters, least productive thread completed %u iters\n", max_iters, min_iters);
    printf("Difference is %u iters\n", diff); 

    return 0;
}
