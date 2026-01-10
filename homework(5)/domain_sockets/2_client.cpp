#include "common.h"
#include <iostream>

int main() {
  int cfd = socket(AF_UNIX, SOCK_STREAM, 0);
  struct sockaddr_un addr;
  prepare_addr(&addr);

  connect(cfd, (struct sockaddr *)&addr, sizeof(addr));

  const char *msg = "biba";
  write(cfd, msg, strlen(msg) + 1);

  char buf[BUF_SIZE];
  read(cfd, buf, sizeof(buf));
  std::cout << "[Client] Server say: " << buf << '\n';

  close(cfd);
  return 0;
}
