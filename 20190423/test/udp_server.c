#include <func.h>
int main(int argc,char *argv[]){
	ARGS_CHECK(argc,3);
	int socketFd;
	socketFd=socket(AF_INET,SOCK_DGRAM,0);
	ERROR_CHECK(socketFd,-1,"socket");
	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));
	ser.sin_addr.s_addr=inet_addr(argv[1]);

	int ret=bind(socketFd,(struct sockaddr*)&ser,sizeof(ser));
	ERROR_CHECK(ret,-1,"bind");
	char buf[128];
	bzero(buf,sizeof(buf));
	struct sockaddr_in client;
	int addrlen=sizeof(client);
	ret=recvfrom(socketFd,buf,5,0,(struct sockaddr*)&client,&addrlen);
	ERROR_CHECK(ret,-1,"recvfrom");
	printf("client ip=%s,port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
	printf("udp sever gets:%s\n",buf);
	bzero(buf,sizeof(buf));
	ret=sendto(socketFd,"world",5,0,(struct sockaddr*)&client,sizeof(client));
	ERROR_CHECK(ret,-1,"sendto");
	close(socketFd);
}
