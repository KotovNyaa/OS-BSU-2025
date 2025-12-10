#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <windows.h>

DWORD StartDummy() {
  STARTUPINFOA si = {sizeof(si)};
  PROCESS_INFORMATION pi;
  if (CreateProcessA("dummy.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si,
                     &pi)) {
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return pi.dwProcessId;
  }
  return 0;
}

void RunKiller(std::string args) {
  std::string cmd = "killer.exe " + args;
  STARTUPINFOA si = {sizeof(si)};
  PROCESS_INFORMATION pi;
  std::vector<char> buf(cmd.begin(), cmd.end());
  buf.push_back(0);

  if (CreateProcessA(NULL, buf.data(), NULL, NULL, FALSE, 0, NULL, NULL, &si,
                     &pi)) {
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
  }
}

bool IsAlive(DWORD pid) {
  HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
  if (hProc == NULL)
    return false;
  DWORD exitCode;
  GetExitCodeProcess(hProc, &exitCode);
  CloseHandle(hProc);
  return (exitCode == STILL_ACTIVE);
}

int main() {
  std::cout << "=== WINDOWS TEST START ===" << std::endl;

  SetEnvironmentVariableA("PROC_TO_KILL", "notepad.exe,dummy.exe,calc.exe");

  std::cout << "\n>>> TEST 1: Kill by --id" << std::endl;
  DWORD pid1 = StartDummy();
  if (pid1 == 0) {
    std::cerr << "Failed to start dummy!" << std::endl;
    return 1;
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  std::cout << "Dummy started (PID: " << pid1 << "). Launching killer..."
            << std::endl;

  RunKiller("--id " + std::to_string(pid1));

  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  if (!IsAlive(pid1))
    std::cout << "[SUCCESS] Dummy is dead." << std::endl;
  else
    std::cout << "[FAIL] Dummy is still alive." << std::endl;

  //----

  std::cout << "\n>>> TEST 2: Kill by ENV (using --name)" << std::endl;
  DWORD pid2 = StartDummy();
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  std::cout << "Dummy started (PID: " << pid2 << "). Launching killer..."
            << std::endl;

  RunKiller("--name");

  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  if (!IsAlive(pid2))
    std::cout << "[SUCCESS] Dummy is dead." << std::endl;
  else
    std::cout << "[FAIL] Dummy is still alive." << std::endl;

  SetEnvironmentVariableA("PROC_TO_KILL", NULL);
  std::cout << "\n=== TEST FINISHED ===" << std::endl;
  return 0;
}
