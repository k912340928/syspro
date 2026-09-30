#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    int c;

    if (argc < 2) {
        fp = stdin;
    } else {
        fp = fopen(argv[1], "r");
        
        if (fp == NULL) {
            fprintf(stderr, "파일을 열 수 없습니다: %s\n", argv[1]);
            return 1;
        }
    }

    while ((c = fgetc(fp)) != EOF) {
        putchar(c);
    }

    if (fp != stdin) {
        fclose(fp);
    }

    return 0;
}
