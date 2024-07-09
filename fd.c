#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main()
{
  int fd;
  char filename[20];
  int max_fds = 0;

  // 尝试打开文件，从fd 3开始（因为0, 1, 2分别是stdin, stdout, stderr）
  for (int i = 3;; i++)
  {
    snprintf(filename, sizeof(filename), "/tmp/testfile%d", i);
    fd = open(filename, O_CREAT | O_RDWR, 0666);

    if (fd == -1)
    {
      // 如果打开文件失败，可能是因为达到了文件描述符的限制
      if (errno == EMFILE || errno == ENFILE)
      {
        printf("Reached the limit of open file descriptors. Max FDs: %d\n", i - 1);
        break;
      }
      else
      {
        // 如果不是由于文件描述符限制导致的错误，则打印错误信息并退出
        perror("open");
        exit(EXIT_FAILURE);
      }
    }

    // 尝试关闭文件描述符
    // close(fd);

    max_fds = i;
  }

  return 0;
}