#include<stdio.h>
#include<signal.h>

int x = 0;

int main()
{
    int pid = fork();
    if(pid == 0)
    {
        x++;
        printf("child process x = %d\n", x);
    }
    else
    {
        wait(NULL);
        x++;
        printf("parent process x = %d\n", x);
    }
}