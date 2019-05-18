#include <func.h>
int main(){
	int fd;
	fd=open("/tmp/log",O_RDWR|O_CREAT);
	ERROR_CHECK(fd,-1,"open");
	time_t local_time;
	char buf[128];
	if(!fork()){
		setsid();
		chdir("/");
		umask(0);
		for(int idx=0;idx<3;++idx){
			close(idx);	
		}	
		while(1){
			sleep(5);
			write(fd,"I have run 5s.\n",strlen("I have run 5s.\n"));
			time(&local_time);
			bzero(buf,sizeof(buf));
			strcpy(buf,ctime(&local_time));
			write(fd,buf,sizeof(buf));		
		}
	}
	else {
		exit(0);
	}
	return 0;
}
