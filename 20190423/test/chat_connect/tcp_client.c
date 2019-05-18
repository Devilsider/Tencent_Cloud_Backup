#include <func.h>
int main(int argc,char *argv[]){
	ARGS_CHECK(argc,3);

	int socketFd;
	socketFd=socket(AF_INET,SOCK_STREAM,0);
	ERROR_CHECK(socketFd,-1,"socket");

	struct sockaddr_in client;
	client.sin_family=AF_INET;
	client.sin_port=htons(atoi(argv[2]));
	client.sin_addr.s_addr=inet_addr(argv[1]);

	int ret=connect(socketFd,(struct sockaddr *)&client,sizeof(client));
	ERROR_CHECK(ret,-1,"connect");
	printf("connect success :)\n");
		
	fd_set rdset;
	char buf[256];
	while(1){
		FD_ZERO(&rdset);
		FD_SET(STDIN_FILENO,&rdset);
		FD_SET(socketFd,&rdset);
		ret=select(socketFd+1,&rdset,NULL,NULL,NULL);
		if(FD_ISSET(STDIN_FILENO,&rdset)){
			bzero(buf,sizeof(buf));	
			read(STDIN_FILENO,buf,sizeof(buf));
			if(0==ret){
				printf("Bye Bye:)\n");
				break;	
			}	
			ret=send(socketFd,buf,strlen(buf)-1,0);
			ERROR_CHECK(ret,-1,"send");
		}	
		if(FD_ISSET(socketFd,&rdset)){
			bzero(buf,sizeof(buf));
			ret=recv(socketFd,buf,sizeof(buf),0);
			ERROR_CHECK(ret,-1,"recv");
			if(0==ret){
				printf("Bye Bye!\n");
				break;	
			}	
			printf("I am client :),gets %s\n",buf);
		}
	}
	close(socketFd);
	return 0;	
}
