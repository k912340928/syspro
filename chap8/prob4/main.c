#include <stdio.h>
#include <stdlib.h>

/* Declare exit handlers as static functions. */
static void exit_handler1(void), exit_handler2(void);

int main(void)
{
    /* Register exit handlers with atexit(). */
    if (atexit(exit_handler1) != 0)
        perror("cannot register exit_handler1");
    if (atexit(exit_handler2) != 0)
        perror("cannot register exit_handler2");

    printf("main done\n");
    exit(0);
}

static void exit_handler1(void)
{
    printf("first exit handler\n");
}

static void exit_handler2(void)
{
    printf("second exit handler\n");
}
