#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int fd[2];
  char buf[32] = {0};

  pipe(fd);

  if (fork() == 0) {
    close(fd[1]);
    read(fd[0], buf, 31);
    std::cout << "[Child] Parent say: " << buf << '\n';
    close(fd[0]);
  } else {
    close(fd[0]);
    write(fd[1], "[Parent] Hello!", 15);
    close(fd[1]);
    wait(NULL);
  }

  return 0;
}
