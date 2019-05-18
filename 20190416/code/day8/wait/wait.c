#include <func.h>

int main()
{
	if(!fork())
	{
		printf("I am child process,pid=%d,ppid=%d\n",getpid(),getppid());
		return 0;
	}else{
		printf("I am prarent\n");
		pid_t childPid;
		childPid=wait(NULL);
		printf("childPid is %d\n",childPid);
		return 0;
	}
}
