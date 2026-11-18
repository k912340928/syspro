#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int pid1, child, status;

    pid1 = fork();
    if (pid1 == 0) {
        execvp(argv[1], &argv[1]);
        fprintf(stderr, "%s : cannot execute\n", argv[1]);
        exit(1);
    } else if (pid1 < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else {
        child = wait(&status);
        printf("[%d] child process %d end\n", getpid(), child);
        printf("\tend code %d\n", status >> 8);
    }
    return 0;
}
