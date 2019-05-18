#include <func.h>
void sigFunc(int signum,siginfo_t *p1,void *p2){
	printf("before sleep,%d is coming \n",signum);
	sleep(3);
	sigset_t pending;
	sigpending(&pending);
	if(sigismember(&pending,SIGQUIT)){
		printf("SIGQUIT is in the pending set!\n");	
	}else {
		printf("SIGQUIT is not in the pending set!\n");	
	}
	printf("after sleep,%d is coming \n.",signum);
}
int main(){
	struct sigaction act;
	bzero(&act,sizeof(act));
	act.sa_flags=SA_SIGINFO;
	act.sa_sigaction=sigFunc;
	sigaddset(&act.sa_mask,SIGQUIT);
	int ret= sigaction(SIGINT,&act,NULL);
	ERROR_CHECK(ret,-1,"sigaction");
	ret= sigaction(SIGQUIT,&act,NULL);
	ERROR_CHECK(ret,-1,"sigaction");
	sleep(5);
	//	while(1);
	return 0;
}
