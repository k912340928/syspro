#include <stdio.h>
#include <stdlib.h>
#include "student.h"

int main(int argc, char *argv[]) {
    struct student rec;
    FILE *fp;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return 1;
    }

    fp = fopen(argv[1], "w");
    if (fp == NULL) {
        fprintf(stderr, "Error: cannot open file %s\n", argv[1]);
        return 1;
    }

    printf("학번  이름  점수\n");

    while (scanf("%d %s %hd", &rec.id, rec.name, &rec.score) == 3) {
        fprintf(fp, "%d %s %d\n", rec.id, rec.name, rec.score);
    }

    fclose(fp);
    return 0;
}
