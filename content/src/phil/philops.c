#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "philops.h"


struct pstruc {
  enum pstate_e state;
  sem_t sem;
};
  
struct pstruc phil[NUM_PHIL];
pthread_mutex_t mutex;


void
init_phil()
{
  for (int i=0;i<NUM_PHIL;i++){
    phil[i].state= THINKING;
    if (sem_init(&phil[i].sem, 0, 0) < 0) {
      perror("sem_init failed");
      exit(-1);
    }
  }
}

/*
  Tests if philosopher i wants to, and can eat
  and if so, does a post (up) to her semaphore.
*/
void
test(int i, int p) {
  // if phil i is hungry and neither of neighbors are eating
  // she gets to eat
  if (phil[i].state == HUNGRY && phil[(i + 1) % NUM_PHIL].state != EATING &&
      phil[(i + NUM_PHIL - 1) % NUM_PHIL].state != EATING) {
    phil[i].state = EATING;
    if (p) fprintf(stderr, "W");
    sem_post(&phil[i].sem); // philosopher[i].up()
  }
}


void
take_chopsticks(int i) 
{
  pthread_mutex_lock(&mutex);
  phil[i].state = HUNGRY;
  test(i, 0);
  pthread_mutex_unlock(&mutex);

  // either post happened in above test,
  // or by test when neighbors put chopstics
  sem_wait(&phil[i].sem); 
}

void
put_chopsticks(int i)
{
  pthread_mutex_lock(&mutex);
  phil[i].state = THINKING;
  test((i + 1) % NUM_PHIL, 1);
  test(((i + NUM_PHIL - 1) % NUM_PHIL), 1);
  pthread_mutex_unlock(&mutex);
}

enum pstate_e 
get_status_phil(int p)
{
  return phil[p].state;
}



