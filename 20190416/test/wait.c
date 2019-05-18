#include <func.h>
int main(){
	pid_t pid=fork();
	if(pid<0){
		printf("create child process wrong!");
		return -1;
	}
	else if(pid==0)
	{
		printf("I am child process,pid=%d,ppid=%d\n",getpid(),getppid());
		return 0;	
	}
	else {
		printf("I am parent process,pid=%d,child=%d\n",getpid(),pid);
		pid_t child_pid;
		child_pid=wait(NULL);
		printf("child_pid is %d\n",child_pid);
		return 0;

	}
}
