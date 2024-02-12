#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <setjmp.h>
#include <assert.h>

static jmp_buf buf;

#include "ec440threads.h"


void
foo()
{
  printf("you called foo\n");
  exit(0);
}

int
main()
{
  setjmp(buf);

  printf("Address of main is %p\n", main);
  printf("PC  is 0x%08lx\n", buf[0].__jmpbuf[JBL_PC]);

  return 0;
}
