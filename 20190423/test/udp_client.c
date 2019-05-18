#include <func.h>
int main(int argc,char *argv[]){
	ARGS_CHECK(argc,3);
	int socketFd;
	socketFd=socket(AF_INET,SOCK_DGRAM,0);
	ERROR_CHECK(socketFd,-1,"socket");
	struct sockaddr_in client;
	client.sin_family=AF_INET;
	client.sin_port=htons(atoi(argv[2]));
	client.sin_addr.s_addr=inet_addr(argv[1]);
	
	int ret;
	ret=sendto(socketFd,"helloworld",10,0,(struct sockaddr *)&client,sizeof(client));
	ERROR_CHECK(ret,-1,"sendto");
	char buf[128]={0};
	ret=recvfrom(socketFd,buf,sizeof(buf),0,NULL,NULL);
	ERROR_CHECK(ret,-1,"recvfrom");
	printf("udp client gets:%s\n",buf);
	close(socketFd);
}
