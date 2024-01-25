#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "doforke.h"

int
main(int argc, char* argv[]) 
{
  char *args[4];

  args[0] = "/usr/bin/ls";
  args[1] = "-al";
  args[2] = 0;
  do_fork_exec("/usr/bin/ls", args);

  args[0] = "/usr/bin/ls";
  args[1] = "-a";
  args[2] = "/usr/bin";
  args[3] = 0;
  do_fork_exec("/usr/bin/ls", args);

  args[0] = "/usr/bin/echo";
  args[1] = "hello class\n";
  args[2] = NULL;
  do_fork_exec("/usr/bin/echo", args);

  return 0;
} 
