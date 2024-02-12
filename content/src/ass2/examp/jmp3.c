#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include <assert.h>
#include "ec440threads.h"

static jmp_buf buf;

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

  printf("Address main is %p\n", main);
  printf("demangled PC  is 0x%08lx\n", _ptr_demangle(buf[0].__jmpbuf[JBL_PC]));
  return 0;
}
