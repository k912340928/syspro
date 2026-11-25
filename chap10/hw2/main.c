#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

/* head, tail은 데이터가 없는 머리 노드이다.
   head->next는 큐의 맨 앞 노드, tail->next는 큐의 맨 뒤 노드를 가리킨다. */

/* addq(): 새 노드를 만들어 큐의 맨 뒤에 넣는다. */
void addq(struct node *head, struct node *tail, int data)
{
    struct node *p = (struct node *) malloc(sizeof(struct node));
    if (p == NULL) {
        perror("malloc");
        exit(1);
    }
    p->data = data;
    p->next = NULL;

    if (head->next == NULL)        /* 큐가 비어 있으면 */
        head->next = p;            /* 새 노드가 맨 앞이 됨 */
    else
        tail->next->next = p;      /* 기존 맨 뒤 노드 뒤에 연결 */
    tail->next = p;                /* 새 노드가 맨 뒤가 됨 */
}

/* delete(): 큐의 맨 앞 노드를 꺼내 값을 반환하고 메모리를 해제한다.
   큐가 비어 있으면 -1을 반환한다. */
int delete(struct node *head, struct node *tail)
{
    struct node *p = head->next;
    int data;

    if (p == NULL)
        return -1;
    data = p->data;
    head->next = p->next;
    if (head->next == NULL)        /* 마지막 노드를 꺼냈으면 */
        tail->next = NULL;         /* tail도 비움 */
    free(p);
    return data;
}

int main()
{
    struct node head, tail;
    int n;

    head.next = NULL;
    tail.next = NULL;

    /* 자연수를 입력받는 동안 계속 addq */
    while (scanf("%d", &n) == 1 && n > 0)
        addq(&head, &tail, n);

    /* 자연수 외의 값이 들어오면 전체 큐를 delete하며 출력 */
    printf("Print queue\n");
    while (head.next != NULL)
        printf("%d\n", delete(&head, &tail));

    return 0;
}
