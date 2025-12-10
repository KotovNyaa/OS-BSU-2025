#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <thread>
#include <unistd.h>

pid_t StartDummy() {
  pid_t pid = fork();
  if (pid == 0) {
    execl("./dummy", "./dummy", (char *)NULL);
    exit(1);
  }
  return pid;
}

void RunKiller(std::string arg1, std::string arg2 = "") {
  pid_t pid = fork();
  if (pid == 0) {
    if (arg2.empty())
      execl("./killer", "./killer", arg1.c_str(), (char *)NULL);
    else
      execl("./killer", "./killer", arg1.c_str(), arg2.c_str(), (char *)NULL);
    exit(1);
  }
  waitpid(pid, NULL, 0);
}

bool IsAlive(pid_t pid) {
  int status;
  pid_t result = waitpid(pid, &status, WNOHANG);

  if (result == 0) {
    return true;
  } else if (result == pid) {
    return false;
  }
  return false;
}

int main() {
  std::cout << "=== LINUX TEST START ===" << std::endl;

  setenv("PROC_TO_KILL", "gedit,dummy,vim", 1);

  std::cout << "\n>>> TEST 1: Kill by --id" << std::endl;
  pid_t pid1 = StartDummy();
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  std::cout << "Dummy started (PID: " << pid1 << "). Launching killer..."
            << std::endl;

  RunKiller("--id", std::to_string(pid1));

  std::this_thread::sleep_for(std::chrono::milliseconds(500));

  if (!IsAlive(pid1))
    std::cout << "[SUCCESS] Dummy is dead." << std::endl;
  else
    std::cout << "[FAIL] Dummy is still alive." << std::endl;

  //---

  std::cout << "\n>>> TEST 2: Kill by ENV (using --name)" << std::endl;
  pid_t pid2 = StartDummy();
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  std::cout << "Dummy started (PID: " << pid2 << "). Launching killer..."
            << std::endl;

  RunKiller("--name");

  std::this_thread::sleep_for(std::chrono::milliseconds(500));

  if (!IsAlive(pid2))
    std::cout << "[SUCCESS] Dummy is dead." << std::endl;
  else
    std::cout << "[FAIL] Dummy is still alive." << std::endl;

  unsetenv("PROC_TO_KILL");
  std::cout << "\n=== TEST FINISHED ===" << std::endl;

  return 0;
}
