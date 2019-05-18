#include "function.h"
int main(int argc,char *argv[]){
	ARGS_CHECK(argc,3);
	int socketFd;
	socketFd=socket(AF_INET,SOCK_STREAM,0);
	ERROR_CHECK(socketFd,-1,"socket");
	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));
	ser.sin_addr.s_addr=inet_addr(argv[1]);
	int ret;
	ret=connect(socketFd,(struct sockaddr *)&ser,sizeof(struct sockaddr_in));
	ERROR_CHECK(ret,-1,"connect");
	printf("connect success :)\n");
	int dataLen;
	char buf[1000];
	recv(socketFd,&dataLen,4,0);
	recv(socketFd,buf,sizeof(buf),0);
	int fd;
	fd=open(buf,O_CREAT|O_WRONLY,0666);
	ERROR_CHECK(fd,-1,"open");
	while(1){
		recv(socketFd,&dataLen,4,0);
		if(dataLen>0){
			recv(socketFd,buf,sizeof(buf),0);
			write(fd,buf,sizeof(buf));	
		}else{
			break;	
		}	
	}	
	close(fd);
	close(socketFd);
	return 0;
}
