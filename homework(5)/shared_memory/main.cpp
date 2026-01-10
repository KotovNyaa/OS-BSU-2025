#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

// g++ main.cpp -o main -lrt

int main() {
  const char *name = "/posix_shm";
  const int SIZE = 4096;

  int fd = shm_open(name, O_CREAT | O_RDWR, 0666);

  ftruncate(fd, SIZE);

  void *ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  if (fork() == 0) {
    const char *msg = "[Child] Hello!";
    memcpy(ptr, msg, strlen(msg) + 1);

    return 0;
  } else {
    wait(NULL);

    std::cout << "[Parent] Child say: " << (char *)ptr << '\n';

    shm_unlink(name);
  }

  return 0;
}
