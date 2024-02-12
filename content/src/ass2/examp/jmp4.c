#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include <assert.h>
#include "ec440threads.h"

jmp_buf buf;

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
  // hey lets play with this...
  // buf[0].__jmpbuf[JB_PC] = ptr_mangle((long unsigned int)foo);
  set_reg(&buf, JBL_PC, (unsigned long int)foo);

  // what is the problem with this?  Why does this work in this case
  // 

  longjmp(buf, 1);
  return 0;
}
