#include <stdio.h>
#include <stdlib.h>

/* Print all environment variables. */
int main(int argc, char *argv[])
{
    char **ptr;
    extern char **environ;

    for (ptr = environ; *ptr != 0; ptr++)    /* print every environment variable */
        printf("%s \n", *ptr);

    exit(0);
}
