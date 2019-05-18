#include <func.h>
int main(){
	pid_t pid =fork();
	if(pid<0){
		printf("creat child process error!\n");	
	}
	else if(pid==0){
		printf("this is child process!\n");
		exit(0);	
	}
	else {
		printf("this is parent process!\n");
		wait(NULL);
		sleep(3);	
	}
	return 0;
}
