#include <func.h>
int main(){
	if(!fork()){
		printf("I am child process!\n");
		int num=1/0;
		printf("num = %d\n",num);
		return 0;	
	}
	else{
		printf("I am parent process!\n");
		pid_t child_pid;
		int status;
		child_pid=wait(&status);
		if(WIFEXITED(status)){
			printf("the child process exit normally!%d\n",WEXITSTATUS(status));		
		}	
		else{
			printf("child crash!\n");	
		}
		printf("the child pid is %d\n",getpid());
		return 0;
	}
}
