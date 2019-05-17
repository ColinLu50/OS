// Sleep in c
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc,char *argv[]) {
	
    if(argc == 2)
	{
		char **end;
		int sleepTime = strtol(argv[1], end, 10);
		printf("I will sleep for %d s\n", sleepTime);
		sleep(sleepTime);
		printf("Woke up!!\n");
		return 0;
	}
	else
	{
		printf("error! format: job4 one_integer\n");
		return 0;
	}
	
}