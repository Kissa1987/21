#include <stdio.h>
#include <string.h>

#include "s21_cat.h"


void print_file(char* name, struct arguments* flags, int* line_number_all) {
    FILE* file = fopen(name, "r");
    int line_printed = 1;

    if (file != NULL) {
        int c = fgetc(file);
        while (c != EOF) {
            if (flags->e == 1 && c == '\n') {
                printf("$");
                line_printed = 1;
            } 
            if (flags->n == 1 && line_printed == 1) {
                printf("\t%d ", *line_number_all);
                line_printed = 0;
            }
           
            putc(c, stdout);
            c = fgetc(file);
        }
        fclose(file);
    }
}

void flags_parser(struct arguments* flags, int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-b") == 0) {
            flags->b = 1;
        } else if (strcmp(argv[i], "-e") == 0) {
            flags->e = 1;
        } else if (strcmp(argv[i], "-n") == 0) {
            flags->n = 1;
        } else if (strcmp(argv[i], "-s") == 0) {
            flags->s = 1;
        } else if (strcmp(argv[i], "-t") == 0) {
            flags->t = 1;
        }
    }
}

int main(int argc, char *argv[]) {
    struct arguments flags = {0}; 

    flags_parser(&flags, argc, argv);
    int line_number_all = 0;
     
    for (int i = 1; i < argc; i++) {
        print_file(argv[i], &flags, &line_number_all);
    }
    return 0;
}