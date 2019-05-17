#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

struct Student{
    char sid[11];
    char name[20];
    int mark;
};
int main(int argc, char * argv[]){
    int num;
    int i;
    printf("Enter record number:\n");
    scanf("%d", &num);
    char sid[]="11210162";
    char name[]="markzxx";
    struct Student stu;
    strcpy(stu.sid,sid);
    strcpy(stu.name,name);
    stu.mark=60;
    FILE * fpd = fopen("student.dat","w");
    FILE * fpb = fopen("student.bin","wb");

    struct timeval begin1, begin2, end1, end2;
    gettimeofday(&begin1, NULL);
    i = num;
    while((i--)>0){
        fprintf(fpd, "%s %s %d ", stu.sid, stu.name, stu.mark);
        
    }
    gettimeofday(&end1, NULL);
    printf("took %lu\n", end1.tv_usec - begin1.tv_usec);
    i = num;
    gettimeofday(&begin2, NULL);
    while((i--)>0){
        fwrite(&stu,sizeof(struct Student),1,fpb);
        
    }
    gettimeofday(&end2, NULL);
    printf("took %lu\n", end2.tv_usec - begin2.tv_usec);
    fclose(fpd);
    fclose(fpb);
    return 0;
}