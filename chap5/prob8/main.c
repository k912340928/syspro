#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define MAXLINE 10
#define MAXLEN 100

char savedText[MAXLINE][MAXLEN];

int main(int argc, char *argv[])
{
    int fd, row = 0, col = 0, total, i;
    char buf;
    char input[100];

    if (argc < 2) {
        fprintf(stderr, "How to use : %s file\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    while (row < MAXLINE && read(fd, &buf, 1) > 0) {
        if (buf == '\n') {
            savedText[row][col] = '\0';
            row++;
            col = 0;
        } else if (buf != '\r' && col < MAXLEN - 1) {
            savedText[row][col++] = buf;
        }
    }
    if (col > 0 && row < MAXLINE) {
        savedText[row][col] = '\0';
        row++;
    }
    close(fd);
    total = row;

    printf("File read success\n");
    printf("Total Line : %d\n", total);
    printf("You can choose 1 ~ %d Line\n", total);
    printf("Pls 'Enter' the line to select : ");

    if (fgets(input, sizeof(input), stdin) == NULL)
        exit(1);
    input[strcspn(input, "\n")] = '\0';

    if (strcmp(input, "*") == 0) {
        for (i = 0; i < total; i++)
            printf("%s\n", savedText[i]);
    } else if (strchr(input, '-') != NULL) {
        int start, end;
        if (sscanf(input, "%d-%d", &start, &end) != 2 ||
            start < 1 || end > total || start > end) {
            printf("Input Error\n");
            exit(1);
        }
        for (i = start; i <= end; i++)
            printf("%s\n", savedText[i - 1]);
    } else {
        char *tok = strtok(input, ",");
        while (tok != NULL) {
            int n = atoi(tok);
            if (n >= 1 && n <= total)
                printf("%s\n", savedText[n - 1]);
            else
                printf("Line %d Null\n", n);
            tok = strtok(NULL, ",");
        }
    }

    exit(0);
}

