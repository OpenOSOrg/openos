#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char* argv[]) 
{
  pid_t mypid, cpid, ppid;
  cpid = fork();
  ppid = getppid();
  mypid = getpid();

  if (cpid > 0) {
    /* Parent code */ 
    printf("hello, from parent with pid %d, pid of child is %d\n", mypid, cpid);
  } else if (cpid == 0) {
    /* Child code */
    printf("hello, I am child with pid %d, my parent is %d\n", mypid, ppid);
  } else {
    perror("fork failed\n");
    exit(-1);
  }
  return 0;
} 
