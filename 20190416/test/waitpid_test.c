#include<func.h>
int main(){
	pid_t pid;
	pid =fork();
	if(!pid){
		printf("I am child process!\n");
		sleep(1);
		return 0;	
	}
	else {
		printf("I am parent!\n");
		pid_t childPid;
		int status;
		childPid=waitpid(pid,&status,WNOHANG);
		if(childPid>0){ 
			if(WIFEXITED(status)){
				printf("child exit normally!\n");			
				printf("%d\n",WEXITSTATUS(status));	
			}	
			else {
				printf("child crash!\n");		
			}
		}
		printf("childPid is %d\n",childPid);
		return 0;	
	}
}
