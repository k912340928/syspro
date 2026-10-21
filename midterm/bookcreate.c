#include <stdio.h> 
#include "student.h"

int main(int argc, char* argv[]) 
{ 
struct Book rec;
FILE *fp;
if (argc != 2) {
fprintf(stderr, "How to use: %s FileName\n", argv[0]);
return 1; 
}
fp = fopen(argv[1], "w");
printf("%-9s %-7s %-4s\n", "book number", "book name", "age"); 
while (scanf("%d %s %d", &rec.book number, rec.book name, &rec.age)==3) 
fprintf(fp, "%d %s %d ", rec.booknumber, rec.book name, rec.age);
fclose(fp);
return 0;
} 
