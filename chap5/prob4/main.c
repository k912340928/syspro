#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int fd1, fd2;

    /* myfile 생성(권한 0600)과 동시에 파일 디스크립터 생성 */
    if ((fd1 = creat("myfile", 0600)) == -1) {
        perror("myfile");
        exit(1);
    }

    write(fd1, "Hello! Linux", 12);   /* 원래 디스크립터로 쓰기 */
    fd2 = dup(fd1);                   /* 파일 디스크립터 복제 */
    write(fd2, "Bye! Linux", 10);     /* 복제한 디스크립터로 쓰기 */

    close(fd1);
    close(fd2);
    exit(0);
}

