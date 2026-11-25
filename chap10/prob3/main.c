#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char str[32] = "Do you like Linux?";
    char *ptr, *p;

    /* malloc(): 32바이트 공간을 동적으로 할당하고 시작 주소를 반환 */
    ptr = (char *) malloc(32);
    if (ptr == NULL) {
        perror("malloc");
        exit(1);
    }

    /* memcpy(): str의 내용을 ptr로 복사 (+1은 문자열 끝 '\0'까지 복사) */
    memcpy(ptr, str, strlen(str) + 1);
    puts(ptr);

    /* memset(): ptr+12 위치부터 1바이트를 'l'로 설정 (L -> l) */
    memset(ptr + 12, 'l', 1);
    puts(ptr);

    /* memchr(): ptr의 18바이트 범위에서 'l'이 처음 나오는 주소를 반환 */
    p = (char *) memchr(ptr, 'l', 18);
    puts(p);

    /* memmove(): str+7부터 10바이트를 str+12로 복사 (영역이 겹쳐도 안전) */
    memmove(str + 12, str + 7, 10);
    puts(str);

    free(ptr);
    return 0;
}
