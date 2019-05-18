#include <func.h>
void sigFunc(int signum){
	printf("%d is coming \n",signum);
}
int main(){
	if(signal(SIGINT,sigFunc)==SIG_ERR){
		perror("signal");
		return -1;	
	}
	char buf[128];
	bzero(buf,sizeof(buf));
	read(STDIN_FILENO,buf,sizeof(buf));
	printf("%s\n",buf);
	return 0;
}
