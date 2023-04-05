#include <stdatomic.h>

typedef struct spinlock_s {
    atomic_flag locked;
} spinlock_t; 

static inline void spinlock_init(spinlock_t *l) {
    atomic_flag_clear( &l->locked );
}

static inline void spinlock_acquire(spinlock_t *l)
{
    while(atomic_flag_test_and_set( &l->locked )) { };
}

static inline void spinlock_release(spinlock_t *l)
{
    atomic_flag_clear( &l->locked );
}
