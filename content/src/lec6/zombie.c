#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
  if (fork()) {
    printf("parent\n");
    sleep(100);
    exit(0);
  } else {
    printf("child\n");
    exit(0);
  }
}
