

#include <stdio.h>

void q();

void foo()
{
  int i=1, j=2;
  q(i+j);
}


int
main()
{
  foo();
  return 0;
}

void q()
{
}
