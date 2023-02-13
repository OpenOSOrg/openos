#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "philops.h"

void *thread_take_chopstick(void *arg){
  unsigned long int i = (unsigned long int)arg;  
  take_chopsticks(i);
  while(1){};
}

void tests()
{
  pthread_t threads[NUM_PHIL];                                                              
  int phil;                                                                                      
  init_phil();

  take_chopsticks(0);
  assert(get_status_phil(0) == EATING);

  // why doesn't this work???
  phil = 1;
  pthread_create(&threads[phil], NULL, thread_take_chopstick, (void *)(intptr_t)(phil)); 
  assert(get_status_phil(phil) == HUNGRY);

  put_chopsticks(0);
  assert(get_status_phil(phil) == EATING);

}

extern void good_tests();

int main(int argc, char **argv) {
  tests();
}


void good_tests()
{
  pthread_t threads[NUM_PHIL];                                                              
  int phil;                                                                                      
  init_phil();

  take_chopsticks(0);
  assert(get_status_phil(0) == EATING);

  // make sure that child blocks
  phil = 1;
  pthread_create(&threads[phil], NULL, thread_take_chopstick, (void *)(intptr_t)(phil)); 
  while(get_status_phil(phil) != HUNGRY) {
    fprintf(stderr, ".");
  }

  assert(get_status_phil(phil) == HUNGRY);

  put_chopsticks(0);
  while (get_status_phil(phil) == HUNGRY) {
    fprintf(stderr, ",");
  }
  assert(get_status_phil(phil) == EATING);

}
