#include<func.h>
void SignChildPsExit(int iSignNo){
	int iExitCode;
	pid_t pid=wait(&iExitCode);
	printf("SignNo:%d, child %d exit\n",iSignNo,pid);
	if(WIFEXITED(iExitCode)){
		printf("child exited with code %d\n",WEXITSTATUS(iExitCode));
	}
	sleep(1);
}
int main(){
	signal(SIGCHLD,SignChildPsExit);
	printf("parent process id:%d\n",getpid());
	pid
