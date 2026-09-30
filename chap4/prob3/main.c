#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    int line = 1;
    char buffer[256];

    // 명령줄 인수가 없으면 사용법 출력
    if (argc < 2) {
        fprintf(stderr, "사용법: %s [파일명]\n", argv[0]);
        return 1;
    }

    // 파일 열기
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        fprintf(stderr, "파일 열기 오류: %s\n", argv[1]);
        return 1;
    }

    // 한 줄씩 읽어 줄 번호(1, 2, 3...)와 함께 출력
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%d %s", line++, buffer);
    }

    fclose(fp);
    return 0;
}
