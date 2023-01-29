#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "doforke.h"

int
main(int argc, char* argv[]) 
{
  char *args[4];
  args[1] = 0;

  args[0] = "-al";
  do_fork_exec("/usr/bin/ls", args);

  args[0] = "-a";
  args[1] = "/usr/bin";
  args[2] = 0;
  do_fork_exec("/usr/bin/ls", args);

  args[0] = "hello class";
  args[1] = 0;
  do_fork_exec("/usr/bin/echo", args);

  return 0;
} 
