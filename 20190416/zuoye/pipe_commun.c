#include <func.h>
int main(){
	int fds[2]={0};
	pipe(fds);
	char buff[256];
	if(!(fork())){
		printf("I am child process\n");
		close(fds[0]);
		strcpy(buff,"Hello World!");
		write(fds[1],buff,sizeof(buff));
		close(fds[1]);
		return 0;	
	}		
	else{
		printf("I am parent process\n");
		close(fds[1]);
		read(fds[0],buff,sizeof(buff));
		puts(buff);
		wait(NULL);
		close(fds[0]);
		return 0;	
	}

}
