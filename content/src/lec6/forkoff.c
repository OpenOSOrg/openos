#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define CHILDREN 10

int main()
{
  int i;
  for (i=1;i<=CHILDREN;i++) {
    if (!fork()) {
      while(1);
    }
  }
  sleep(3);
  exit(0);
}
