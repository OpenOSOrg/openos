#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <bsd/sys/time.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <semaphore.h>

atomic_bool started = false;

/* Begin Courtois et al. reader/writer semaphore solution with reader priority here */
static void read_db();
static void write_db();

sem_t mutex;         /* Initially 1 */
sem_t counter_mutex; /* Initially 1 */
int reader_count = 0;

static void writer()
{
    sem_wait(&mutex);
    write_db();
    sem_post(&mutex);
}

static void reader()
{
    
    sem_wait(&counter_mutex);
    reader_count++;
    if (reader_count == 1) {
        /* first reader synchronizes with writers to acquire the resource */
        sem_wait(&mutex);
    }
    sem_post(&counter_mutex);
    
    read_db();
    
    sem_wait(&counter_mutex);
    reader_count--;
    if (reader_count == 0) {
        /* last reader releases the resource */
        sem_post(&mutex);
    }
    sem_post(&counter_mutex);
}
/* End Courtois et al. reader/writer semaphore solution with reader priority. */

static void *writer_thread(void *arg)
{
    long niters = (long)arg;
    long i;
    
    while(!started) ; /* spin until all threads are ready */
        
    for (i = 0; i < niters; i++) {
        writer();
    }
    return (void *)0;
}

static void *reader_thread(void *arg)
{
    long niters = (long)arg;
    long i;
    
    while(!started) ; /* spin until all threads are ready */

    for (i = 0; i < niters; i++) {
        reader();
    }
    return (void *)0;
}

int main(int argc, char **argv)
{
    pthread_t *tids;
    long niters;
    int nreaders, nwriters, nthreads, i;
    
    if (argc != 4) {
        fprintf(stderr,"Usage: %s <num_readers> <num_writers> <num_iters>\n",argv[0]);
        return 1;
    }

    nreaders = atoi(argv[1]);
    nwriters = atoi(argv[2]);
    niters = atol(argv[3]);
    
    printf("Main thread: Beginning test with %d readers and %d writers, each doing %ld iterations\n", 
           nreaders, nwriters, niters);
    sem_init(&counter_mutex, 0, 1);
    sem_init(&mutex, 0, 1);
    
    nthreads = nreaders + nwriters;
    tids = (pthread_t *)malloc(nthreads * sizeof(pthread_t));
    
    /* We create the requested number of reader and writer threads, each doing the same number of iterations. 
     * When all threads have completed, we report the throughput. 
     */
    for (i = 0; i < nreaders; i++) {
        (void)pthread_create(&tids[i], NULL, reader_thread, (void *)niters );
    }
    
    for(i = 0; i < nwriters; i++) {
        (void)pthread_create(&tids[i+nreaders], NULL, writer_thread, (void *)niters );
    }
    
    struct timespec strt;
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &strt);
    started = true;
    /* Wait for child threads to finish */
    for (i = 0; i < nthreads; i++) {
        pthread_join(tids[i], NULL);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    
    /* report performance statistics */    
    struct timespec diff;
    timespecsub(&end, &strt, &diff);
    float elapsed_sec = diff.tv_sec + diff.tv_nsec / 1000000000.0;
    printf("Main thread: Completed %ld iterations in %f seconds (%f iters per second)\n",
          niters*nthreads, elapsed_sec, niters*nthreads*1.0/elapsed_sec);

    return 0;
}

static void read_db() 
{
    return;
}

static void write_db()
{
    return;
}