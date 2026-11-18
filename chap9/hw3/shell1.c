#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 1024
#define MAXARG  64

void run_command(char *cmd)
{
    char *args[MAXARG];
    char *infile = NULL, *outfile = NULL;
    char *token, *saveptr;
    int argc = 0, background = 0;
    int pid, status, fd, len;

    /* 1. 끝에 & 가 있으면 후면 실행 */
    len = strlen(cmd);
    while (len > 0 && (cmd[len-1] == ' ' || cmd[len-1] == '\t'))
        cmd[--len] = '\0';
    if (len > 0 && cmd[len-1] == '&') {
        background = 1;
        cmd[--len] = '\0';
    }

    /* 2. 공백으로 나누고 < > 처리 */
    token = strtok_r(cmd, " \t", &saveptr);
    while (token != NULL && argc < MAXARG - 1) {
        if (strcmp(token, ">") == 0)
            outfile = strtok_r(NULL, " \t", &saveptr);
        else if (strcmp(token, "<") == 0)
            infile = strtok_r(NULL, " \t", &saveptr);
        else
            args[argc++] = token;
        token = strtok_r(NULL, " \t", &saveptr);
    }
    args[argc] = NULL;

    if (argc == 0)
        return;
    if (strcmp(args[0], "exit") == 0)
        exit(0);

    /* 3. 자식 생성 */
    pid = fork();
    if (pid < 0) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        if (infile != NULL) {
            fd = open(infile, O_RDONLY);
            if (fd < 0) { perror(infile); exit(1); }
            dup2(fd, 0);
            close(fd);
        }
        if (outfile != NULL) {
            fd = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0600);
            if (fd < 0) { perror(outfile); exit(1); }
            dup2(fd, 1);
            close(fd);
        }
        execvp(args[0], args);
        fprintf(stderr, "%s: command not found\n", args[0]);
        exit(127);
    }

    /* 4. 부모: 전면이면 기다리고, 후면이면 안 기다림 */
    if (background)
        printf("[%d] background\n", pid);
    else
        waitpid(pid, &status, 0);
}

int main()
{
    char line[MAXLINE];
    char *cmd, *saveptr;

    while (1) {
        while (waitpid(-1, NULL, WNOHANG) > 0)
            ;

        printf("[shell] ");
        fflush(stdout);

        if (fgets(line, MAXLINE, stdin) == NULL) {
            printf("\n");
            break;
        }
        line[strcspn(line, "\n")] = '\0';

        /* ; 로 나눠서 순서대로 실행 */
        cmd = strtok_r(line, ";", &saveptr);
        while (cmd != NULL) {
            run_command(cmd);
            cmd = strtok_r(NULL, ";", &saveptr);
        }
    }
    return 0;
}
