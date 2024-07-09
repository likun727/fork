#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
  pid_t pid = fork();
  if (pid > 0)
  {
    /* 父进程 */
    int wstatus;
    int i = 1;
    while (i--)
    {
      sleep(1);
      printf("parent message: child pid:%d\n", pid);
    }
    int ret = wait(&wstatus);
    if (ret == -1)
    {
      perror("wait ");
      return -1;
    }
    printf("child exit status is : %d\n", WEXITSTATUS(wstatus));
  }
  else if (pid == 0)
  {
    /* 子进程 */
    }
  else
  {
    perror("fork error");
    return -1;
  }

  return 0;
}
