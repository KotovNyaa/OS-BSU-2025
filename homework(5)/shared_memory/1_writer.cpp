#include "common.h"
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

// g++ 1_writer.cpp -o 1_writer -lrt

int main() {
  int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
  ftruncate(fd, SHM_SIZE);

  void *ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  const char *msg = "[Writer] Hello!";
  memcpy(ptr, msg, strlen(msg) + 1);

  std::cout << "[Writer] Data written to SHM. Waiting 10 seconds...\n";
  sleep(10);

  shm_unlink(SHM_NAME);
  return 0;
}
