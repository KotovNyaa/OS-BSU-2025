#include <chrono>
#include <iostream>
#include <thread>

#include <windows.h>
#define GET_PID() GetCurrentProcessId()

int main() {
  auto pid = GET_PID();
  std::cout << "[Dummy] I am alive. My PID is: " << pid << std::endl;

  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  return 0;
}
