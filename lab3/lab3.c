#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HISTORY_SIZE 5

void add_to_history(char *history[], int *count, char *buff);
void print_history(char *history[], int count);
void free_history(char *history[], int count);

int main(void) {
  char *history[HISTORY_SIZE] = {NULL};
  int count = 0;

  while (1) {
    char *buff = NULL;
    size_t size = 0;
    ssize_t num_char;

    printf("Enter input: ");

    num_char = getline(&buff, &size, stdin);

    if (num_char == -1) {
      free(buff);
      break;
    }

    add_to_history(history, &count, buff);

    if (strcmp(buff, "print\n") == 0) {
      print_history(history, count);
    }
  }

  free_history(history, count);

  return 0;
}

void add_to_history(char *history[], int *count, char *buff) {
  if (*count == HISTORY_SIZE) {
    free(history[0]);

    for (int i = 1; i < HISTORY_SIZE; i++) {
      history[i - 1] = history[i];
    }

    history[HISTORY_SIZE - 1] = buff;
  } else {
    history[*count] = buff;
    (*count)++;
  }
}

void print_history(char *history[], int count) {
  for (int i = 0; i < count; i++) {
    printf("%s", history[i]);
  }
}

void free_history(char *history[], int count) {
  for (int i = 0; i < count; i++) {
    free(history[i]);
    history[i] = NULL;
  }
}
