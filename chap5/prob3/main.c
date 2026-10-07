#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFSIZE 512

/* 파일 복사 프로그램 */
int main(int argc, char *argv[])
{
    int fd1, fd2;
    ssize_t n;
    char buf[BUFSIZE];

    /* 입력 인자가 3개가 아니면 사용법 출력 */
    if (argc != 3) {
        fprintf(stderr, "How to use: %s file1 file2\n", argv[0]);
        exit(1);
    }

    /* 원본 파일: 읽기 모드 */
    if ((fd1 = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    /* 새 파일: 쓰기 | 생성 | 내용 지우기, 권한 0600 */
    if ((fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0600)) == -1) {
        perror(argv[2]);
        exit(3);
    }

    /* BUFSIZE 단위로 반복해서 읽고 쓰기 */
    while ((n = read(fd1, buf, BUFSIZE)) > 0)
        write(fd2, buf, n);   /* 읽은 내용을 쓴다 */

    close(fd1);
    close(fd2);
    exit(0);
}

