#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char *buff = NULL;
  size_t size = 0;
  ssize_t num_char;

  // Loop to keep accepting new input
  while (1) {
    printf("Please enter some text: ");

    // Read a full line of text from the keyboard
    num_char = getline(&buff, &size, stdin);

    // Error handling for getline()
    if (num_char == -1) {
      perror("getline failed");
      free(buff);
      exit(EXIT_FAILURE);
    }

    printf("Tokens:\n");

    // Tokenization setup using saveptr for thread safety
    char *saveptr;

    // 1st call to strtok_r: pass in the full string (buff)
    char *token = strtok_r(buff, " ", &saveptr);

    // Loop to process and print all tokens
    while (token != NULL) {
      printf("  %s\n", token);

      // 2nd+ calls to strtok_r: pass in NULL
      token = strtok_r(NULL, " ", &saveptr);
    }
  }

  // Free the dynamically allocated buffer
  free(buff);

  return 0;
}
