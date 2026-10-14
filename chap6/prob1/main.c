#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Main function: Checks and prints the file type for each file path given as command-line arguments */
int main(int argc, char *argv[])
{
    int i;
    struct stat buf;

    /* Iterate through all command-line arguments passed to the program */
    for (i = 1; i < argc; i++) {
        printf("%s: ", argv[i]);

        /* Retrieve file status using lstat(). If it fails, print an error message and continue to the next argument. */
        if (lstat(argv[i], &buf) < 0) {
            perror("lstat()");
            continue;
        }

        /* Check file types using S_IS* macros based on st_mode */
        if (S_ISREG(buf.st_mode))
            printf("%s\n", "Regular File");
        if (S_ISDIR(buf.st_mode))
            printf("%s\n", "Directory");
        if (S_ISCHR(buf.st_mode))
            printf("%s\n", "Character Device");
        if (S_ISBLK(buf.st_mode))
            printf("%s\n", "Block Device");
        if (S_ISFIFO(buf.st_mode))
            printf("%s\n", "FIFO (Named Pipe)");
        if (S_ISLNK(buf.st_mode))
            printf("%s\n", "Symbolic Link");
        if (S_ISSOCK(buf.st_mode))
            printf("%s\n", "Socket");
    }

    exit(0);
}
