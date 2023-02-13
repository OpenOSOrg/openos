#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

pthread_barrier_t *barrier;

int main(int argc, char **argv)
{
  printf("Testing that barrier with count of 0 results in EINVAL.\n");
  barrier = malloc(sizeof(*barrier));
  int init_status = pthread_barrier_init(barrier, NULL, 0);
  assert(init_status == EINVAL);
  printf("Barrier with count of 0 results in error!\n\n");
  
  printf("Testing if barrier can be created.\n");
  init_status = pthread_barrier_init(barrier, NULL, 3);
  assert(init_status == 0);
  printf("Barrier can be created!\n\n");
  
  printf("Testing if barrier can be destroyed.\n");
  int barrier_status = pthread_barrier_destroy(barrier);
  assert(barrier_status == 0);
  printf("Barrier can be destroyed!\n\n");
  
  printf("Testing if barrier can be initialized after being destroyed.\n");
  init_status = pthread_barrier_init(barrier, NULL, 3);
  assert(init_status == 0);
  printf("Barrier can be initialized after being destroyed!\n\n");
  
  printf("Finished Barrier testing.\n\n");
  
  return 0;
}
