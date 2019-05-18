#include <func.h> 
void sigFunc(int signum){
	printf("before sleep,signal %d is coming!\n",signum);
	sleep(3);
	printf("after sleep,signal %d is coming!\n",signum);
}
int main(){
	if(signal(SIGINT,sigFunc)==SIG_ERR){
		perror("signal");
		return -1;	
	}
	if(signal(SIGQUIT,sigFunc)==SIG_ERR)
	{
		perror("signal");
		return -1;
	}
	while(1);
}
