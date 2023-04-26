#include <semaphore.h>

typedef struct rwlock_s {
    sem_t mutex;
    sem_t counter_mutex;
    int reader_count;
} rwlock_t; 

static inline void rwlock_init(rwlock_t *l) {
    l->reader_count = 0;
    sem_init(&l->counter_mutex, 0, 1);
    sem_init(&l->mutex, 0, 1);
}

static inline void rwlock_acquire_write(rwlock_t *l)
{
    sem_wait(&l->mutex);
}

static inline void rwlock_release_write(rwlock_t *l)
{
    sem_post(&l->mutex);
}

static inline void rwlock_acquire_read(rwlock_t *l)
{
    sem_wait(&l->counter_mutex);
    l->reader_count++;
    if (l->reader_count == 1) {
        /* first reader synchronizes with writers to acquire the resource */
        sem_wait(&l->mutex);
    }
    sem_post(&l->counter_mutex);   
}

static inline void rwlock_release_read(rwlock_t *l)
{
    sem_wait(&l->counter_mutex);
    l->reader_count--;
    if (l->reader_count == 0) {
        /* last reader releases the resource */
        sem_post(&l->mutex);
    }
    sem_post(&l->counter_mutex);
}
