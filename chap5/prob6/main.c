#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"

int main(int argc, char *argv[])
{
    int fd, id;
    char c;
    struct student record;

    if (argc < 2) {
        fprintf(stderr, "How to use : %s file\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    do {
        printf("Enter StudentID to search : ");
        if (scanf("%d", &id) == 1) {
            if (id >= START_ID &&
                lseek(fd, (id - START_ID) * sizeof(record), SEEK_SET) != -1 &&
                read(fd, (char *) &record, sizeof(record)) > 0 &&
                record.id != 0)
                printf("StuID:%d\t Name:%s\t Score:%d\n",
                       record.id, record.name, record.score);
            else
                printf("Record %d Null\n", id);
        } else {
            printf("Input Error\n");
            while (getchar() != '\n');
        }
        printf("Continue?(Y/N)");
        scanf(" %c", &c);
    } while (c == 'Y');

    close(fd);
    exit(0);
}

