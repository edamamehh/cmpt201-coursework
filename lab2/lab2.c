#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char *line = NULL;
  size_t len = 0;
  ssize_t input;

  while (1) {
    printf("Enter programs to run.\n");
    printf("> ");
    fflush(stdout);

    // Read input
    input = getline(&line, &len, stdin);

    if (input == -1) {
      break;
    }

    // Tokenize using strtok_r
    char *saveptr;
    char *cmd = strtok_r(line, " \t\n", &saveptr);

    if (cmd == NULL) {
      continue;
    }

    pid_t pid = fork();

    if (pid < 0) {
      perror("Fork failed");
      continue;
    } else if (pid == 0) {
      execl(cmd, cmd, (char *)NULL);

      printf("Exec failure\n");
      exit(1);
    } else {
      int status;
      waitpid(pid, &status, 0);
    }
  }

  free(line);
  return 0;
}
