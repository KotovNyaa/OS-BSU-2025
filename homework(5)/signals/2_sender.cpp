#include <iostream>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  pid_t target_pid = std::stoi(argv[1]);

  std::cout << "[Sender] Sending SIGUSR1 to process " << target_pid << "...\n";

  kill(target_pid, SIGUSR1);

  return 0;
}
