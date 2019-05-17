#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	printf("caller PID : %d\n", getpid());
	if(fork() == 0)
	{
		execl("/bin/ls", "/bin/ls", NULL);
		execl("./lab2_run", "./lab2_run",  NULL);
	}
	wait(NULL);
	printf("11610310 luning\n");
	return 0;
}
