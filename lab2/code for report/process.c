#include <stdio.h>
#include <signal.h>
#include <stddef.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <sys/termios.h>

int main()  // http://www.cnblogs.com/kele-dad/p/9169444.html
{
	int cpid;/* 保存子进程的id号 */
	int ppid;/* 保存父进程的id号 */
	char buf[256];

	ppid=getpid();//得到近程号
	cpid=fork();
	  

	if (cpid<0)
		exit(-1);
	
	if (!cpid)//子进程
	{
		fprintf(stdout,"ID(child)=%d\n",getpid());
	
		/* 使子进程所在的进程组成为前台进程组，然后执行vi */
		setpgid(0,0);
		tcsetpgrp(0,getpid());
		execl("/usr/bin/vi","vi",NULL);
		fprintf(stdout,"ID(child)=%d\n",getpid());
		exit(-1);

	}
	
	fprintf(stdout,"ID(parent)=%d\n",ppid);
	setpgid(cpid,cpid);/* 设置进程组 */
	tcsetpgrp(0,cpid);/* 设置控制终端为子进程拥有 */
	waitpid(cpid,NULL,0);/* 父进程等待子进程执行完毕，所在进程组成为前台进程组 */
	signal(SIGTTOU,SIG_IGN);
	tcsetpgrp(0,ppid);
	//父进程等待终端输入，然后回显
	while(1)
	{
		memset(buf, 0, 256);
		fgets(buf, 256, stdin);
		puts("ECHO: ");
		puts(buf);
		puts("\n");
	}
	
	return 0;
}
