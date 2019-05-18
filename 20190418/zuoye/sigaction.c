#include <func.h>
void sigFunc(int signum,siginfo_t *p1,void *p2){
   	printf("the signal num is %d.\n",signum);
}
int main(){
	struct sigaction act;
	bzero(&act,sizeof(act));
	act.sa_sigaction=sigFunc;
	act.sa_flags=SA_SIGINFO;
	int ret=sigaction(SIGINT,&act,NULL);
	ERROR_CHECK(ret,-1,"sigaction");
	while(1);
	return 0;
}
