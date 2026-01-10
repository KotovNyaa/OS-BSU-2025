#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int sv[2];

  socketpair(AF_UNIX, SOCK_STREAM, 0, sv);

  if (fork() == 0) {
    close(sv[0]);

    char buffer[1024];
    read(sv[1], buffer, sizeof(buffer));
    std::cout << "[Child] Parent say: " << buffer << '\n';

    const char *msg = "boba";
    write(sv[1], msg, strlen(msg) + 1);

    close(sv[1]);
    return 0;
  } else {
    close(sv[1]);

    const char *msg = "biba";
    write(sv[0], msg, strlen(msg) + 1);

    char buffer[1024];
    read(sv[0], buffer, sizeof(buffer));
    std::cout << "[Parent] Child say: " << buffer << '\n';

    wait(NULL);
    close(sv[0]);
  }

  return 0;
}
