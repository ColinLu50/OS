#include<stdio.h>
#include<signal.h>

int main(){
        
    int pid;
    pid = fork();

    if(pid == 0)
    {
        sleep(2);
        kill(getppid(), SIGKILL);
        while(1){
            printf("parent pid = %d",getppid());
        }
    }
    else
    {
        while(1)
        {
            printf("hello, \n");
            sleep(1);
        }
    }
    return 0;
}

