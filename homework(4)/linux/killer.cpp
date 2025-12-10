#include <cstdlib>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <signal.h>
#include <sstream>
#include <string>
#include <unistd.h>

void KillByPid(int pid) {
  if (kill(pid, SIGKILL) == 0) {
    std::cout << " [Killer] Sent SIGKILL to " << pid << std::endl;
  } else {
    perror(" [Killer] Failed to kill");
  }
}

std::string GetName(int pid) {
  std::string path = "/proc/" + std::to_string(pid) + "/comm";
  std::ifstream f(path);
  std::string name;
  if (f >> name)
    return name;
  return "";
}

void KillByName(const std::string &target) {
  DIR *dir = opendir("/proc");
  if (!dir)
    return;

  struct dirent *ent;
  while ((ent = readdir(dir)) != NULL) {
    if (isdigit(ent->d_name[0])) {
      int pid = std::stoi(ent->d_name);
      if (GetName(pid) == target) {
        std::cout << " [Killer] Found " << target << " (PID " << pid << ")"
                  << std::endl;
        KillByPid(pid);
      }
    }
  }
  closedir(dir);
}

void CheckEnv() {
  char *env = getenv("PROC_TO_KILL");
  if (env) {
    std::stringstream ss(env);
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
