#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Main function: Reads and prints the target path of a symbolic link using readlink() */
int main(int argc, char *argv[])
{
    char buffer[1024];
    int nread;

    /* Check command-line argument count */
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <symlink_name>\n", argv[0]);
        exit(1);
    }

    /* Read symbolic link content using readlink() */
    nread = readlink(argv[1], buffer, 1024);

    if (nread > 0) {
        write(1, buffer, nread); /* Print the link path to standard output */
        write(1, "\n", 1);        /* Print newline character */
        exit(0);
    } else {
        fprintf(stderr, "Error : No such link\n"); /* Print error message if invalid link */
        exit(1);
    }
}
