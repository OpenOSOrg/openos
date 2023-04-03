#include <stdatomic.h>

typedef struct ticketlock_s {
    atomic_ulong next_ticket;
    atomic_ulong now_serving;
} ticketlock_t; 

static inline void ticketlock_init(ticketlock_t *l) {
    l->next_ticket = 0;
    l->now_serving = 0;
}

static inline void ticketlock_acquire(ticketlock_t *l)
{
    unsigned long my_ticket = atomic_fetch_add(&l->next_ticket, 1);
    while(my_ticket != l->now_serving) { };
}

static inline void ticketlock_release(ticketlock_t *l)
{
    l->now_serving++;
}
