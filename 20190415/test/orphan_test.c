#include <func.h>
int main(){
	pid_t pid = fork();
	if(pid<0){
		printf("create child process error!\n");
	}
	else if(pid==0){
		printf("this is child process!\n");
		printf("self pid is %d,child pid is %d\n",getpid(),getppid());	
		while(1){
					
		}
	}
	else {
		printf("this is parent process!\n");
		exit(0);
	}
	sleep(1);
	return 0;
}
