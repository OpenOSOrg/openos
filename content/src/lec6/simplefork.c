#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int children = 0;
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

#define SLEEP_TIME 2
#define CHILDREN 2

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
      
