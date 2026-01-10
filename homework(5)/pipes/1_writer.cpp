#include "common.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
  mkfifo(FIFO_PATH, 0666);

  int fd = open(FIFO_PATH, O_WRONLY);
  write(fd, "[Writer] Hello!", 15);
  close(fd);

  return 0;
}
