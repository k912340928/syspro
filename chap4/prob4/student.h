#ifndef STUDENT_H
#define STUDENT_H

#define MAX_NAME 20

struct student {
    int  id;                 /* 학번 */
    char name[MAX_NAME];     /* 이름 */
    int  score;              /* 점수 */
};

#endif
