
#include <string.h>
#include <stdio.h>
#include <errno.h>

int main(int argc,char* argv[])
{
	int pid;
	char *prog_argv[4];

	/* ���������� */
	prog_argv[0]="/bin/ls";
	prog_argv[1]="-l";
	prog_argv[2]="/";
	prog_argv[3]=NULL;
	
	/* Ϊ����ls�������� */
	if ((pid=fork())<0)
	{
		perror("Fork failed");
		exit(errno);
	}
	
	if (!pid)/* �����ӽ��̣�ִ������ls */
	{
		printf("argc = %d, argv[0] = %s",argc,argv[0]);
		execvp(prog_argv[0],prog_argv);
	}
	
	if (pid)/* ���Ǹ����̣��ȴ��ӽ���ִ�н���*/
	{
		waitpid(pid,NULL,0);
	}
	
	return 0;
}

