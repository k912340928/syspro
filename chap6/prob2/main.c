#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

/* Main function: Changes the access permission of a given file */
int main(int argc, char *argv[])
{
    long strtol();
    int newmode;

    /* Check command-line argument count */
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <octal_mode> <filename>\n", argv[0]);
        exit(1);
    }

    /* Convert string argument (octal format) to integer mode */
    newmode = (int) strtol(argv[1], (char **) NULL, 8);

    /* Change file permission using chmod() system call.
       If the file does not exist or fails, print error message using perror() */
    if (chmod(argv[2], newmode) == -1) {
        perror(argv[2]);
        exit(1);
    }

    exit(0);
}
