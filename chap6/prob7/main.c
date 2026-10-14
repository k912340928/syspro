#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/* Main function: Removes a link for a given file path using unlink() */
int main(int argc, char *argv[])
{
    /* Check command-line argument count */
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename_or_link>\n", argv[0]);
        exit(1);
    }

    /* Remove file link using unlink() system call.
       If the file does not exist or deletion fails, print error message using perror() */
    if (unlink(argv[1]) == -1) {
        perror(argv[1]);
        exit(1);
    }

    exit(0);
}
