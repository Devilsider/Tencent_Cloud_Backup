#include <func.h>
int main(){
	pid_t pid=fork();
	if(pid<0){
		printf("Create child process fail!\n");
	}
	else if(pid==0){
		printf("child process id:%d,ppid:%d\n",getpid(),getppid());
	}
	else {
		printf("parent process sucess,my child id:%d,self id:%d\n",pid,getpid());
	}
	sleep(1);
	return 0;
}
