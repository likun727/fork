#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
  int i;
  for (i = 0; i < 5; ++i)
  {
    sleep(1);
  }
  exit(i);
}