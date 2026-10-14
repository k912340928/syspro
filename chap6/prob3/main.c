#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <utime.h>
#include <stdio.h>
#include <stdlib.h>

/* Main function: Copies the access and modification times from file1 to file2 */
int main(int argc, char *argv[])
{
    struct stat buf;      /* Variable to store file status */
    struct utimbuf time;  /* Variable to store access/modification times */

    /* Check command-line argument count */
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <source_file> <target_file>\n", argv[0]);
        exit(1);
    }

    /* Step 1: Retrieve status/time information of source file (argv[1]) */
    if (stat(argv[1], &buf) < 0) {
        perror("stat()");
        exit(-1);
    }

    /* Step 2: Copy access time and modification time from stat buffer */
    time.actime = buf.st_atime;
    time.modtime = buf.st_mtime;

    /* Step 3: Apply the copied times to target file (argv[2]) */
    if (utime(argv[2], &time)) {
        perror("utime()");
        exit(1);
    }

    exit(0);
}
