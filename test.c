#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
  char buf[64];
  printf("Enter a thing:\n");
  fflush(0);
  scanf("%s", buf);
  printf("%s\n%s\n", "test function", buf);

  fflush(stdout);

  return 0;
}