#include "common.h"
#include <iostream>

int main() {
  int sfd = socket(AF_UNIX, SOCK_STREAM, 0);
  struct sockaddr_un addr;
  prepare_addr(&addr);

  unlink(SOCKET_PATH);
  bind(sfd, (struct sockaddr *)&addr, sizeof(addr));
  listen(sfd, 1);

  int cfd = accept(sfd, NULL, NULL);

  char buf[BUF_SIZE];
  read(cfd, buf, sizeof(buf));
  std::cout << "[Server] Client say: " << buf << '\n';

  const char *msg = "boba";
  write(cfd, msg, strlen(msg) + 1);

  close(cfd);
  close(sfd);
  unlink(SOCKET_PATH);
  return 0;
}
