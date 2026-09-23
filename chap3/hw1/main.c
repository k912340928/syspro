#include <stdio.h>
#include <string.h>
#include "copy.h"

#define N 5

char lines[N][MAXLINE];
char temp[MAXLINE];
char line[MAXLINE];

int main(void)
{
    int i, j, len;
    int count = 0;

    while (count < N && fgets(line, MAXLINE, stdin) != NULL) {
        len = strlen(line);
        if (len > 0 && line[len-1] == '\n')
            line[len-1] = '\0';
        copy(line, lines[count]);
        count++;
    }

    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count; j++) {
            if (strlen(lines[j]) > strlen(lines[i])) {
                copy(lines[i], temp);
                copy(lines[j], lines[i]);
                copy(temp, lines[j]);
            }
        }
    }

    for (i = 0; i < count; i++)
        printf("%s\n", lines[i]);

    return 0;
}
