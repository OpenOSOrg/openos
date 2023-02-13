// This test case covers the basics of mutex implementation.

#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>

pthread_mutex_t *mutex;
pthread_mutexattr_t Attr;
int child_blocked = 0;
int child_holding_lock = 0;
int child_done = 0;


void *
child_routine( void *arg)
{
  // child acquires lock

  child_blocked = 1;
  printf("Testing if child can acquire lock.\n");
  int lock_status = pthread_mutex_lock(mutex);
  assert(lock_status == 0);
  printf("Mutex can be locked by child!\n\n");

  child_holding_lock = 1;
  sleep(1);

  printf("Testing if mutex can be unlocked by child.\n");
  lock_status = pthread_mutex_unlock(mutex);
  assert(lock_status == 0);
  printf("Mutex can be unlocked.\n\n");
  
  child_done = 1;
  while(1){};
}

int main(int argc, char **argv)
{
  pthread_t child_thread;                                                              

  printf("Testing if mutex can be created.\n");
  mutex = malloc(sizeof(*mutex));
  int init_status = pthread_mutex_init(mutex, NULL);
  assert(init_status == 0);
  printf("Mutex created!\n\n");
  
  printf("Testing if mutex can be locked.\n");
  int lock_status = pthread_mutex_lock(mutex);
  assert(lock_status == 0);
  printf("Mutex can be locked!\n\n");
  
  pthread_create(&child_thread, NULL, child_routine, NULL); 
  while (!child_blocked) {
    fprintf(stderr, ".");
  }
  
  printf("Testing if mutex can be unlocked.\n");
  lock_status = pthread_mutex_unlock(mutex);
  assert(lock_status == 0);
  printf("Mutex can be unlocked.\n\n");
  
  while (!child_holding_lock) {
    fprintf(stderr, ".");
  }

  printf("Testing if mutex can be locked after child unlock.\n");
  lock_status = pthread_mutex_lock(mutex);
  assert(lock_status == 0);
  printf("Mutex can be locked after unlock.\n\n");
  
  printf("Testing if mutex can be unlocked.\n");
  lock_status = pthread_mutex_unlock(mutex);
  assert(lock_status == 0);
  printf("Mutex can be unlocked.\n\n");
  
  printf("Testing if mutex can be destroyed.\n\n");
  lock_status = pthread_mutex_destroy(mutex);
  assert(lock_status == 0);
  printf("Mutex can be destroyed!\n\n");
  
  printf("Testing if mutex can be initialized after being destroyed.\n");
  init_status = pthread_mutex_init(mutex, NULL);
  printf("Mutex can be initialized after being destroyed!\n\n");
  
  printf("Finished Mutex testing.\n\n");
  
  exit(0);
}
