#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

long int shared_counter;

static void *increment_thread(void *arg)
{
    int niters = (int)arg;
    for (int i = 0; i < niters; i++) {
        shared_counter++;
    }

    return (void *)0;
}

static void *decrement_thread(void *arg)
{
    int niters = (int)arg;

    for (int i = 0; i < niters; i++) {
        shared_counter--;
    }

    return (void *)0;
}

int main(int argc, char **argv)
{
    pthread_t *tids;
    int niters, nthreads, i;
    
    if (argc != 3) {
        fprintf(stderr,"Usage: %s <num_threads> <num_iters>\n",argv[0]);
        return 1;
    }

    nthreads = atoi(argv[1]);
    niters = atoi(argv[2]);
    shared_counter = 0;
    
    printf("Main thread: Beginning test with %d threads\n", nthreads);
    
    tids = (pthread_t *)malloc(nthreads * sizeof(pthread_t));
    
    /* We create the same number of increment and decrement threads, each doing the same number of iterations. 
     * When all threads have completed, we expect the final value of the shared counter to be the same as its
     * initial value (i.e., 0).
     */
    for (i = 0; i < nthreads/2; i++) {
        (void)pthread_create(&tids[i], NULL, increment_thread, (void *)niters );
        (void)pthread_create(&tids[i+1], NULL, decrement_thread, (void *)niters );
    }
    
    /* Wait for child threads to finish */
    for (i = 0; i < nthreads/2; i++) {
        pthread_join(tids[i], NULL);
        pthread_join(tids[i+1], NULL);
    }
    
    printf("Main thread: Final value of shared counter is %ld\n", shared_counter);

    return 0;
}