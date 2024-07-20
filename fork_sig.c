#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

void catchChild(int signo)
{
  pid_t wpid;
  int wstatus;
  // wpid = wait(&wstatus);
  // printf("ret val : %d \n", WEXITSTATUS(wstatus));
  while ((wpid = waitpid(-1, &wstatus, 0)) != -1)
  {
    if (WIFEXITED(wstatus))
    {
      printf("exit success %d  ----- ret val : %d \n", wpid, WEXITSTATUS(wstatus));
    }
    else
    {
      printf("child process exit abnormally\n");
      // exit(-1);
    }
  }
}

int main()
{
  pid_t pid;
  int i;
  // 阻塞 防止父进程还没注册成功子进程就结束了
  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set, SIGCHLD);
  sigprocmask(SIG_BLOCK, &set, NULL);
  for (i = 0; i < 5; i++)
  {
    if ((pid = fork()) == 0)
    {
      break;
    }
    else if (pid < 0)
    {
      perror("fork");
      exit(-1);
    }
  }

  if (i == 5)
  {
    // 父进程
    struct sigaction act;

    act.sa_handler = catchChild;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, NULL);

    printf("register success\n");
    sigprocmask(SIG_UNBLOCK, &set, NULL);
    sleep(10);
  }
  else
  {
    printf("child process\n");
    return i;
  }

  return 0;
}