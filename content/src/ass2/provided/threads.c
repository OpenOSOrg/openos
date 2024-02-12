#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <setjmp.h>
#include <assert.h>
#include "ec440threads.h"


#define MAX_THREADS 128		        /* number of threads you support */
#define THREAD_STACK_SIZE (1<<15)	/* size of stack in bytes */
#define QUANTUM (50 * 1000)	        /* quantum in usec */

/* 
   Thread_status identifies the current state of a thread. What states could a thread be in?
   Values below are just examples you can use or not use. 
 */
enum thread_status
{
 TS_EXITED,
 TS_RUNNING,
 TS_READY
};

/* The thread control block stores information about a thread. You will
 * need one of this per thread. What information do you need in it? 
 * Hint, remember what information Linux maintains for each task?
 */
struct thread_control_block {
};


static void schedule(int signal)
{
  /* 
     TODO: implement your round-robin scheduler, e.g., 
     - if whatever called us is not exiting 
       - mark preempted thread as runnable
       - save state of preempted thread
     - determin which thread should be running next
     - mark thread you are context switching to as running
     - restore registers of that thread
   */
}

// to supress compiler error saying these static functions may not be used...
static void schedule(int signal) __attribute__((unused));


static void scheduler_init()
{
  /* 
     TODO: do everything that is needed to initialize your scheduler.
     For example:
     - allocate/initialize global threading data structures
     - create a TCB for the main thread. so your scheduler will be able to schedule it
     - set up your timers to call scheduler...
  */
}

int pthread_create(
	pthread_t *thread, const pthread_attr_t *attr,
	void *(*start_routine) (void *), void *arg)
{
  // Create the timer and handler for the scheduler. Create thread 0.
  static bool is_first_call = true;
  if (is_first_call) {
    is_first_call = false;
    scheduler_init();
  }
  
  /* TODO: Return 0 on successful thread creation, non-zero for an error.
   *       Be sure to set *thread on success.
   *
   * You need to create and initialize a TCB (thread control block) including:
   * - Allocate a stack for the thread
   * - Set up the registers for the functions, including:
   *   - Assign the stack pointer in the thread's registers to point to its stack. 
   *   - Assign the program counter in the thread's registers.
   *   - figure out how to have pthread_exit invoked if thread returns
   * - After you are done, mark your new thread as READY
   * Hint: Easiest to use setjmp to save a set of registers that you then modify, 
   *       and look at notes on reading/writing registers saved by setjmp using 
   * Hint: Be careful where the stackpointer is set to it may help to draw
   *       an empty stack diagram to answer that question.
   * Hint: Read over the comment in header file on start_thunk before 
   *       setting the PC.
   * 
   * Don't forget to assign RSP too! Functions know where to
   * return after they finish based on the calling convention (AMD64 in
   * our case). The address to return to after finishing start_routine
   * should be the first thing you push on your stack.
   */
  return -1;
}

void pthread_exit(void *value_ptr)
{
  /* TODO: Exit the current thread instead of exiting the entire process.
   * Hints:
   * - Release all resources for the current thread. CAREFUL though.
   *   If you free() the currently-in-use stack then do something like
   *   call a function or add/remove variables from the stack, bad things
   *   can happen.
   * - Update the thread's status to indicate that it has exited
   * What would you do after this?
   */
  exit(1);
}

pthread_t pthread_self(void)
{
  /* 
   * TODO: Return the current thread instead of -1, note it is up to you what ptread_t refers to
   */
  return -1;
}

int pthread_join(pthread_t thread, void **retval)
{
  return -1;
}

/* 
 * Don't implement main in this file!
 * This is a library of functions, not an executable program. If you
 * want to run the functions in this file, create separate test programs
 * that have their own main functions.
 */
