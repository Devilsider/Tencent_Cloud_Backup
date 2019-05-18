#include <func.h>
void sigFunc(int signum){
	time_t t;
	t=time(NULL);
	puts(ctime(&t));
}
int main(){
	signal(SIGVTALRM,sigFunc);
	struct itimerval it;
	bzero(&it,sizeof(it));
	it.it_value.tv_sec=3;
	it.it_interval.tv_sec=2;
	int ret=setitimer(ITIMER_VIRTUAL,&it,NULL);
	ERROR_CHECK(ret,-1,"setitimer");
	char buf[256];
	bzero(&buf,sizeof(buf));
	read(STDIN_FILENO,buf,sizeof(buf));
	puts(buf);
	sleep(5);
	while(1);
	return 0;	
}

