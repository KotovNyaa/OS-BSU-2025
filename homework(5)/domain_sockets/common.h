#pragma once
#include <cstring>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/uds.sock"
#define BUF_SIZE 1024

inline void prepare_addr(struct sockaddr_un *addr) {
  memset(addr, 0, sizeof(struct sockaddr_un));
  addr->sun_family = AF_UNIX;
  strncpy(addr->sun_path, SOCKET_PATH, sizeof(addr->sun_path) - 1);
}
