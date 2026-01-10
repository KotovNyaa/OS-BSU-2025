#include <iostream>
#include <signal.h>
#include <unistd.h>

void signal_handler(int sig) { write(1, "[Receiver] Signal received\n", 27); }

int main() {
  signal(SIGUSR1, signal_handler);

  std::cout << "[Receiver] My PID: " << getpid() << "\n";
  std::cout << "[Receiver] Waiting for signal...\n";

  pause();

  return 0;
}
