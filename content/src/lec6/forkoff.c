#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
  int i;
  for (i=1;i<=5;i++) {
    if (!fork()) {
      printf("child %d\n", i);
      while(1);
    }
  }
  sleep(30);
}
