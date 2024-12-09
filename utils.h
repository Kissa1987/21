#ifndef UTILS_H
#define UTILS_H
#define BUFFER_SIZE 1024

#include <stdio.h>
#include <string.h>
#include <unistd.h>

int is_empty_string(const char *line) {
  return (line == NULL || strlen(line) == 0);
}

void print_line(const char *line, int line_number, int show_number,
                int show_end, int show_tabs) {
  if (show_number) {
    dprintf(STDOUT_FILENO, "%6d\t", line_number);
  }

  if (show_tabs) {
    for (const char *p = line; *p != '\0'; p++) {
      if (*p == '\t') {
        write(STDOUT_FILENO, "^I", 2);
      } else {
        write(STDOUT_FILENO, p, 1);
      }
    }
  } else {
    write(STDOUT_FILENO, line, strlen(line));
  }

  if (show_end) {
    write(STDOUT_FILENO, "$", 1);
  }

  write(STDOUT_FILENO, "\n", 1);
}

#endif
