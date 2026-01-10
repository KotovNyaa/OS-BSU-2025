#include "common.h"
#include <fcntl.h>
#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>

// g++ 2_reader.cpp -o 2_reader -lrt

int main() {
  int fd = shm_open(SHM_NAME, O_RDWR, 0666);

  void *ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  std::cout << "[Reader] Received: " << (char *)ptr << '\n';

  return 0;
}
