#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
jmp_buf env[3];
int threads[3] = {0,0,0};

enum {
      RETURN_FROM_LONGJ = 5
};


void
schedule()
{
  static int next_thread = 0;
  if (next_thread == 3) next_thread = 0;
  longjmp(env[next_thread++], RETURN_FROM_LONGJ);
}

void
a()
{
  if (threads[0]==0) {
    if((threads[0] = setjmp(env[0])) != RETURN_FROM_LONGJ) return;
  }
  printf("a() runs\n");
  sleep(1);
  schedule();
}

void
b()
{
  if (threads[1]==0) {
    if( (threads[1] = setjmp(env[1])) != RETURN_FROM_LONGJ) return;
  }
  printf("b() runs\n");
  sleep(1);
  schedule();
}

void
c()
{
  if (threads[2]==0) {
    if( (threads[2] = setjmp(env[2])) != RETURN_FROM_LONGJ) return;
  }

  printf("c() runs\n");
  sleep(1);
  schedule();
}

int main()
{
  printf("suspending\n");
  a();
  b();
  c();
  
  printf("running\n");
  schedule();
}
