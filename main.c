#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  FILE *f = fopen("a.txt", "a+");
  if (!f)
  {
    perror("open file");
    return 0;
  }
  printf("open file success\n");
  pid_t pid = fork();
  if (pid > 0)
  {
    // 父进程
    char buff[] = "parent process";
    size_t num_written = fwrite(buff, sizeof(char), sizeof(buff) - 1, f);
    if (num_written != sizeof(buff) - 1)
    {
      perror("Error writing to file");
      return -1;
    }
    fclose(f);
    printf("fclose\n");
  }
  else if (pid == 0)
  {
    // 子进程
    char buff[] = "child process";
    printf("child process write\n");
    size_t num_written = fwrite(buff, sizeof(char), sizeof(buff) - 1, f);
    if (num_written != sizeof(buff) - 1)
    {
      perror("Error writing to file");
      return -1;
    }
    else
    {
      printf("write success\n");
      return 0;
    }
  }
  else
  {
    perror("fork");
    return -1;
  }

  return 0;
}
