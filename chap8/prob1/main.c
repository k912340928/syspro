#include <stdio.h>
#include <stdlib.h>

/* Print all command-line arguments. */
int main(int argc, char *argv[])
{
    int i;

    for (i = 0; i < argc; i++)    /* print every argument */
        printf("argv[%d]: %s \n", i, argv[i]);

    exit(0);
}
