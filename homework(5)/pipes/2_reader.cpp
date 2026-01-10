#include "common.h"
#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>

int main() {
  char buf[32] = {0};

  int fd = open(FIFO_PATH, O_RDONLY);
  read(fd, buf, 31);
  std::cout << "[Reader] Writer say: " << buf << '\n';
  close(fd);

  unlink(FIFO_PATH);

  return 0;
}
