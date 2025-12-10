#undef UNICODE
#undef _UNICODE

#include <iostream>
#include <sstream>
#include <string>
#include <tlhelp32.h>
#include <windows.h>

void KillByPid(DWORD pid) {
  HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
  if (hProcess == NULL) {
    std::cerr << " [Killer] Failed to open PID " << pid << std::endl;
    return;
  }
  if (TerminateProcess(hProcess, 0)) {
    std::cout << " [Killer] Terminated PID " << pid << std::endl;
  }
  CloseHandle(hProcess);
}

void KillByName(const std::string &name) {
  HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if (hSnap == INVALID_HANDLE_VALUE)
    return;

  PROCESSENTRY32 pe;
  pe.dwSize = sizeof(PROCESSENTRY32);

  if (Process32First(hSnap, &pe)) {
    do {
      if (std::string(pe.szExeFile) == name) {
        std::cout << " [Killer] Found " << name << " (PID " << pe.th32ProcessID
                  << ")" << std::endl;
        KillByPid(pe.th32ProcessID);
      }
    } while (Process32Next(hSnap, &pe));
  }
  CloseHandle(hSnap);
}

void CheckEnv() {
  const DWORD size = 32767;
  char buf[size];
  if (GetEnvironmentVariable("PROC_TO_KILL", buf, size) > 0) {
    std::string envVal = buf;
    std::stringstream ss(envVal);
    std::string segment;
    while (std::getline(ss, segment, ',')) {
      if (!segment.empty())
        KillByName(segment);
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc >= 3 && std::string(argv[1]) == "--id") {
    KillByPid(std::stoi(argv[2]));
  } else if (argc >= 2 && std::string(argv[1]) == "--name") {
    if (argc >= 3)
      KillByName(argv[2]);
    CheckEnv();
  } else {
    CheckEnv();
  }
  return 0;
}
