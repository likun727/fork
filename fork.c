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
    int count = 0;
    while (1)
    {
      sleep(1);
      printf("parent message: child pid:%d\n", pid);
      count++;
      int ret = waitpid(pid, &wstatus, WNOHANG);
      if (ret == pid)
      {
        printf("child exit status is : %d  while count is %d \n", WEXITSTATUS(wstatus), count);
        return 0;
      }
    }
    // int ret = wait(&wstatus);
    // if (ret == -1)
    // {
    //   perror("wait ");
    //   return -1;
    // }
    // printf("child exit status is : %d\n", WEXITSTATUS(wstatus));
  }
  else if (pid == 0)
  {
    /* 子进程 */
    int ret = execl("/home/likun/workspace/linux_set/fork/hmwork/build/task", "t", NULL);
    if (ret < 0)
    {
      perror("exec");
      return -1;
    }
    printf("sdadas");
    printf("sdadas");
    printf("sdadas");
    printf("sdadas");
    printf("sdadas");
  }
  else
  {
    perror("fork error");
    return -1;
  }

  return 0;
}
