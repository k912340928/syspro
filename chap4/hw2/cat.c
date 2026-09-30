#include <stdio.h>
#include <string.h>

void file_dump(FILE *fp, int show_line_num, int *line_num) {
    int c;
    int is_start_of_line = 1;

    while ((c = getc(fp)) != EOF) {
        if (show_line_num && is_start_of_line) {
            printf("%6d  ", (*line_num)++);
            is_start_of_line = 0;
        }
        putc(c, stdout);
        if (c == '\n') {
            is_start_of_line = 1;
        }
    }
}

int main(int argc, char *argv[]) {
    FILE *fp;
    int show_line_num = 0;
    int start_index = 1;
    int line_num = 1;

    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        show_line_num = 1;
        start_index = 2;
    }

    if (start_index >= argc) {
        file_dump(stdin, show_line_num, &line_num);
    } else {
        for (int i = start_index; i < argc; i++) {
            fp = fopen(argv[i], "r");
            if (fp == NULL) {
                perror(argv[i]);
                continue;
            }
            file_dump(fp, show_line_num, &line_num);
            fclose(fp);
        }
    }

    return 0;
}
