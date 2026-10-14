#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/* Main function: Creates a symbolic link pointing to the specified target path */
int main(int argc, char *argv[])
{
    /* Check command-line argument count */
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <actual_path> <symlink_name>\n", argv[0]);
        exit(1);
    }

    /* Create symbolic link using symlink() system call.
       If creation fails, print error message using perror() */
    if (symlink(argv[1], argv[2]) == -1) {
        perror(argv[1]);
        exit(1);
    }

    exit(0);
}
