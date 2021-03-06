#pragma once

#include <sys/wait.h>

namespace waybar::util::command {

struct res {
  int exit_code;
  std::string out;
};

inline struct res exec(const std::string cmd)
{
  FILE* fp(popen(cmd.c_str(), "r"));
  if (!fp) {
    return { -1, "" };
  }

  std::array<char, 128> buffer = {0};
  std::string output;
  while (feof(fp) == 0) {
    if (fgets(buffer.data(), 128, fp) != nullptr) {
      output += buffer.data();
    }
  }

  // Remove last newline
  if (!output.empty() && output[output.length()-1] == '\n') {
    output.erase(output.length()-1);
  }
  int exit_code = WEXITSTATUS(pclose(fp));
  return {exit_code, output};
}

inline bool forkExec(std::string cmd) {
  if (cmd == "") return true;

  printf("fork exec command %s\n", cmd.c_str());
  int32_t pid = fork();

  if (pid < 0) {
    printf("Unable to exec cmd %s, error %s", cmd.c_str(), strerror(errno));
    return false;
  }

  // Child executes the command
  if (!pid) execl("/bin/sh", "sh", "-c", cmd.c_str(), (char*)0);

  return true;
}

}  // namespace waybar::util::command
