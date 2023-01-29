#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "doforke.h"


int
doforke(char *prog, char *const argv[])
{
  pid_t cpid;
  int status=0;
  cpid = fork();
  if (cpid < 0) {
    perror("fork failed\n");
    exit(-1);
  }

  if (cpid != 0) {
    // parent code, we need to wait for child
    waitpid(cpid,&status,0);
  } else {
    execve(prog, argv, 0);
    perror("should never get here\n");
  }
  return status;
} 
