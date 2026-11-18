#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 1024
#define MAXARG  64

int main()
{
    char line[MAXLINE];
    char *args[MAXARG];
    char *token, *saveptr;
    int argc, background, pid, child, status;

    while (1) {
        /* 끝난 후면 프로세스 회수 (좀비 방지) */
        while (waitpid(-1, NULL, WNOHANG) > 0)
            ;

        /* (1) 프롬프트를 내고 명령어 입력 */
        printf("Pls input cmd : ");
        fflush(stdout);
        if (fgets(line, MAXLINE, stdin) == NULL)
            break;
        line[strcspn(line, "\n")] = '\0';

        /* (2) strtok_r()로 명령줄 인수 분리 -> args[] */
        argc = 0;
        background = 0;
        token = strtok_r(line, " \t", &saveptr);
        while (token != NULL && argc < MAXARG - 1) {
            args[argc++] = token;
            token = strtok_r(NULL, " \t", &saveptr);
        }
        args[argc] = NULL;

        if (argc == 0)
            continue;

        /* 마지막 인수가 & 이면 후면 실행 */
        if (strcmp(args[argc-1], "&") == 0) {
            background = 1;
            args[--argc] = NULL;
            if (argc == 0)
                continue;
        }

        if (strcmp(args[0], "exit") == 0) {
            printf("Parent process end\n");
            printf("Exit\n");
            break;
        }

        printf("[%d] Parent process start\n", getpid());
        fflush(stdout);

        /* (3) 자식 생성 -> execvp()로 명령어 실행 */
        pid = fork();
        if (pid < 0) {
            perror("fork");
            continue;
        }
        if (pid == 0) {
            printf("[%d] child process start\n", getpid());
            fflush(stdout);
            execvp(args[0], args);
            fprintf(stderr, "%s: command not found\n", args[0]);
            exit(127);
        }

        /* (4) 부모는 자식이 끝나기를 기다림 (후면이면 안 기다림) */
        if (background) {
            printf("[%d] background process %d\n", getpid(), pid);
        } else {
            child = waitpid(pid, &status, 0);
            printf("[%d] child process end %d\n", getpid(), child);
            if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
                printf("SUCCESS\n");
            else
                printf("FAIL\n");
        }
        printf("\n");
        /* (5) (1)로 돌아가 반복 */
    }
    return 0;
}
