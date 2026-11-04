#include <stdio.h>
#include <unistd.h>

/* Print the current process ID and the parent process ID. */
int main()
{
    printf("my process number: [%d]\n", getpid());          /* current process ID */
    printf("my parent process number: [%d]\n", getppid());  /* parent process ID */
    return 0;
}
