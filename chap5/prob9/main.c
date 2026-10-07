#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define MAXLINE 10
#define MAXLEN 100

char savedText[MAXLINE][MAXLEN];

int main(int argc, char *argv[])
{
    int fd, row = 0, col = 0, i;
    char buf;

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

    for (i = row - 1; i >= 0; i--)
        printf("%s\n", savedText[i]);
    printf("\n");

    exit(0);
}

