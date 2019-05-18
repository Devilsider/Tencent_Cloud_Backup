#include<func.h>
int main(){
	pid_t pid=fork();
	if(pid<0){
		printf("create child process error!\n");
	}
	else if(pid==0){
		printf("this is child process.\n");
		printf("self pid is %d,parent's pid is %d\n",getpid(),getppid());
		printf("the uid is %d,the euid is %d\n",getuid(),geteuid());
		printf("the gid is %d,the egid is %d\n",getgid(),getegid());
	}
	else{
		printf("this is parent process.\n");
		printf("self pid is %d,child pid is %d\n",getpid(),pid);
		printf("the uid is %d,the euid is %d\n",getuid(),geteuid());
		printf("the gid is %d,the egid is %d\n",getgid(),getegid());
	}
	sleep(1);
	return 0;
}
