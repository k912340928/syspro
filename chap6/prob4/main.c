#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

/* Main function: Lists all files in the given directory */
int main(int argc, char **argv)
{
    DIR *dp;
    char *dir;
    struct dirent *d;
    struct stat st;
    char path[BUFSIZ + 1];

    /* Step 1: Set directory path from argument or default to current directory */
    if (argc == 1)
        dir = ".";
    else
        dir = argv[1];

    /* Open directory using opendir().
       If access fails (permission denied or directory does not exist), exit program. */
    if ((dp = opendir(dir)) == NULL) {
        perror(dir);
        exit(1);
    }

    /* Step 2: Iterate through all directory entries using readdir() */
    while ((d = readdir(dp)) != NULL) {
        /* Print filename and i-node number */
        printf("%s %lu\n", d->d_name, d->d_ino);
    }

    /* Step 3: Close directory stream */
    closedir(dp);
    exit(0);
}
