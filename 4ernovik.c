
#include "utils.h"
#include <ctype.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void process_file(int fd, int show_number, int show_end, int show_tabs,
                  int suppress_empty) {
  char buffer[BUFFER_SIZE];
  char line[BUFFER_SIZE];
  int bytes_read;
  int line_number = 0;
  int line_number_blank = 0;
  int prev_empty = 0;
  int has_printed_empty = 0;
  while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
    for (int j = 0; j < bytes_read; j++) {
      if (buffer[j] == '\n' || j == bytes_read - 1) {
        line[line_number] = '\0';
        int is_empty = is_empty_string(line);
        if (suppress_empty) {
          if (is_empty) {
            if (!has_printed_empty) {
              print_line(line, line_number, show_number, show_end, show_tabs);
              has_printed_empty = 1;
            }
            prev_empty = 1;
            continue;
          } else {
            prev_empty = 0;
            has_printed_empty = 0;
          }
        }

        print_line(line, line_number, show_number, show_end, show_tabs);
        if (!is_empty_string(line)) {
          line_number++;
        }
      } else {
        line[line_number] = buffer[j];
        line_number++;
      }
    }
  }
}

int main(int argc, char *argv[]) {
  int show_number = 0;
  int show_end = 0;
  int show_tabs = 0;
  int suppress_empty = 0;

  int opt;
  while ((opt = getopt(argc, argv, "benst")) != -1) {
    switch (opt) {
    case 'b':
      show_number = 1;
      break;
    case 'e':
      show_end = 1;
      break;
    case 't':
      show_tabs = 1;
      break;
    case 's':
      suppress_empty = 1;
      break;
    case 'n':
      show_number = 1;
      suppress_empty = 0;
      break;
    default:
      exit(EXIT_FAILURE);
    }
  }

  if (optind == argc) {
    process_file(STDIN_FILENO, show_number, show_end, show_tabs,
                 suppress_empty);
  } else {
    for (int i = optind; i < argc; i++) {
      int fd = open(argv[i], O_RDONLY);
      if (fd != -1) {
        process_file(fd, show_number, show_end, show_tabs, suppress_empty);
        close(fd);
      } else {
      }
    }
  }

  return 0;
}
