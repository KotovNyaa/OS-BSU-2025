#include <iostream>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

void signal_handler(int sig) { write(1, "[Child] Signal received\n", 24); }

int main() {
  signal(SIGUSR1, signal_handler);

  pid_t pid = fork();

  if (pid == 0) {
    std::cout << "[Child] Waiting for signal...\n";

    pause();

  } else {
    sleep(1);

    std::cout << "[Parent] Sending SIGUSR1 to child (" << pid << ")...\n";

    kill(pid, SIGUSR1);

    wait(NULL);
    std::cout << "[Parent] Child finished. Exiting.\n";
  }

  return 0;
}
