#include <func.h>
void sigFunc(int signum,siginfo_t *p1,void *p2){
	printf("before sleep,%d is coming !\n",signum);
	sleep(3);
	sigset_t pending;
	sigpending(&pending);
	if(sigismember(&pending,SIGQUIT)){
		printf("%d is pending!\n",signum);
	}
	else{
		printf("%d is not pending!\n",signum);	
	}
	printf("after sleep,%d is coming !\n",signum);
}
int main(){
	int ret;
	
	sigset_t proMask;
	sigemptyset(&proMask);	
	sigaddset(&proMask,SIGINT);
	ret=sigprocmask(SIG_BLOCK,&proMask,NULL);
	ERROR_CHECK(ret,-1,"sigprocmask");
	struct sigaction act;
	act.sa_flags=SA_SIGINFO;
	act.sa_sigaction=sigFunc;
	ret=sigaction(SIGQUIT,&act,NULL);
	ERROR_CHECK(ret,-1,"sigaction");
	ret=sigaction(SIGINT,&act,NULL);
	ERROR_CHECK(ret,-1,"sigaction");
	sleep(5);
	ret=sigprocmask(SIG_UNBLOCK,&proMask,NULL);
	ERROR_CHECK(ret,-1,"sigprocmask");
	while(1);
	return 0;	
}
