#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

/* push(): 새 노드를 만들어 스택의 맨 위(top 바로 다음)에 넣는다.
   top은 실제 데이터가 없는 머리 노드(더미 노드)이다. */
void push(struct node *top, int data)
{
    struct node *p = (struct node *) malloc(sizeof(struct node));
    if (p == NULL) {
        perror("malloc");
        exit(1);
    }
    p->data = data;
    p->next = top->next;
    top->next = p;
}

/* pop(): 스택의 맨 위 노드를 꺼내 값을 반환하고 메모리를 해제한다.
   스택이 비어 있으면 -1을 반환한다. */
int pop(struct node *top)
{
    struct node *p = top->next;
    int data;

    if (p == NULL)
        return -1;
    data = p->data;
    top->next = p->next;
    free(p);
    return data;
}

int main()
{
    struct node top;    /* 스택의 머리 노드 */
    int n;

    top.next = NULL;

    /* 자연수를 입력받는 동안 계속 push */
    while (scanf("%d", &n) == 1 && n > 0)
        push(&top, n);

    /* 자연수 외의 값이 들어오면 전체 스택을 pop하며 출력 */
    printf("Print stack\n");
    while (top.next != NULL)
        printf("%d\n", pop(&top));

    return 0;
}
