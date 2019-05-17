#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int fork_num;
	printf("this process id %d before fork\n", getpid());
	fork_num = fork();
	if(fork_num == 0)
	{
		printf("fork return value  is %d\n", fork_num);
		printf("child id is %d\n", getpid());
	}
	else
	{
		printf("fork return value  is %d\n", fork_num);
		printf("parent id is %d\n", getpid());
	}
	return 0;
}
