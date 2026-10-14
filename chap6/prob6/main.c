#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/* Main function: Creates a hard link for a given original file */
int main(int argc, char *argv[])
{
    /* Check command-line argument count */
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <existing_file> <new_link>\n", argv[0]);
        exit(1);
    }

    /* Create hard link using link() system call.
       If the file does not exist or link fails, print error message using perror() */
    if (link(argv[1], argv[2]) == -1) {
        perror(argv[1]);
        exit(1);
    }

    exit(0);
}
