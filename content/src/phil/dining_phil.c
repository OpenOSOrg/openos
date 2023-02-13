#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "philops.h"



void
think(int i)
{
  sleep(.01);			/* won't work with homework 2 */
}

void
eat(int i)
{
  fprintf(stderr, "(%d)", i);
}

void 
philosopher(int i) {
  think(i);
  take_chopsticks(i);
  eat(i);
  put_chopsticks(i);
}

void *runphil(void *arg){
  unsigned long int me = (unsigned long int)arg;
  int count = (me*10+10);  // run each philosopher for num*5+10

  
  fprintf(stderr, "philosopher %ld running for %d\n", me, count);

  sleep(1);			/* won't work with homework 2 */

  for (int i=0; i<count;i++) {
    philosopher(me);
  }
  fprintf(stderr, "\nphilosopher %ld - done\n", me);
  return 0;
}

int main(int argc, char **argv) {
  pthread_t threads[NUM_PHIL];                                                              
  int i;                                                                                      
  init_phil();
  for(i = 0; i < NUM_PHIL; i++) {                                                           
    pthread_create(&threads[i], NULL, runphil, (void *)(intptr_t)(i));                        }                                                                                           

  /* Collect statuses of the other threads, waiting for them to finish */                     
  for(i = 0; i < NUM_PHIL; i++) {                                                           
    pthread_join(threads[i], NULL);                                                     
  }                                                                                           
  return 0;
}
