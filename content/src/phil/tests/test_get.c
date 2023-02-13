#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "philops.h"


int main(int argc, char **argv) {
  init_phil();

  // following routines assume few NUM_PHIL
  assert(NUM_PHIL>4);

#if 1
  assert(NUM_PHIL>20);
#endif
  
  // try a simple routine of getting chopstics in middle
  take_chopsticks(NUM_PHIL/2);
  assert(get_status_phil(NUM_PHIL/2) == EATING);

  // return chockpsitcs 
  put_chopsticks(NUM_PHIL/2);
  assert(get_status_phil(NUM_PHIL/2) == THINKING);

  // check if 0 based
  take_chopsticks(0);
  // assert(get_status_phil(NUM_PHIL/2) == EATING);
  assert(get_status_phil(0) == EATING);

  put_chopsticks(0);
  assert(get_status_phil(0) == THINKING);

  return 0;
}
