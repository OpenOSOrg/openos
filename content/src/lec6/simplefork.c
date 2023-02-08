#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*
 * Goal
 * - demonstrates a simple sinple handler
 * - shows how parent and single handler can coordinate through global variables
 * - style comments constants...
 * - useful for showing how to debug multiple processes 
 */

int children = 0;		/* number of children that have not exited */
void do_something(int signo)
{
  int status, pid;

  fprintf (stderr, "\n-- got signal\n");
  while ((pid = waitpid(0, &status, WNOHANG))>0){
    if( WIFEXITED(status))
      fprintf (stderr, "child %d exit %d\n", pid, WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
      fprintf(stderr, "child %d kill by %d\n", pid, WTERMSIG(status));
    children--;
  }
  fprintf(stderr, "-- done signal handler\n");

}

void init_sigaction()
{
  struct sigaction act;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;
  act.sa_handler = do_something;
  sigaction(SIGCHLD, &act, NULL);
}

void child_function(int seconds)
{
  int pid = getpid();
  while(pid > 0) {
    pid = getpid();
    fprintf(stderr, "[c pid %d]", pid);
    sleep(seconds);
  }
  exit(0);
}

#define SLEEP_TIME 2		/* amount of time children sleep before exiting */
#define CHILDREN   2		/* number of children to fork */

int main()
{
  pid_t pid;
  int i;

  init_sigaction();
  
  children = CHILDREN;
  // start children
  for (i=0; i<CHILDREN; i++ ) {
    pid = fork();
    if (pid==0) {
      child_function(SLEEP_TIME);
    }
  }

  while (children > 0){
    fprintf (stderr, "[p pid - %d]", getpid());
    sleep(SLEEP_TIME);
  }
  return 0;
}
      
