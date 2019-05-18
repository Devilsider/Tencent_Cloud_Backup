#include <func.h>
int main(int argc,char **argv){
	ARGS_CHECK(argc,2);
	int fd=open(argv[1],O_RDWR);
	ERROR_CHECK(fd,-1,"open");
	pid_t pid=fork();
	if(pid<0){
		printf("create child fork error!");
	}
	else if(pid==0){
		printf("this is child fork!\n");
		write(fd,"world!",strlen("world!")-1);
	}
	else {
		printf("this is parent fork!\n");
		write(fd,"hello!",strlen("hello!")-1);
	}
	sleep(1);
	return 0;
}
