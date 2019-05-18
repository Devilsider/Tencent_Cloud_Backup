#include <func.h>
int main(int argc,char *argv[]){
	ARGS_CHECK(argc,3);
	int socketFd;
	socketFd=socket(AF_INET,SOCK_STREAM,0);
	ERROR_CHECK(socketFd,-1,"socket");
	struct sockaddr_in ser;
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));
	ser.sin_addr.s_addr=inet_addr(argv[1]);
	
	int ret;
	ret=bind(socketFd,(struct sockaddr *)&ser,sizeof(ser));
	ERROR_CHECK(ret,-1,"bind");
	listen(socketFd,10);
	int new_fd;
	struct sockaddr_in client;
	bzero(&client,sizeof(client));
	int addrlen=sizeof(client);
	new_fd=accept(socketFd,(struct sockaddr *)&client,&addrlen);
	printf("client ip:%s,port:%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
	char buf[128];
	bzero(buf,sizeof(buf));
//	ret=recv(new_fd,buf,sizeof(buf)i,0);
	ERROR_CHECK(ret,-1,"recv");
	printf("ret=%d,buf=%s\n",ret,buf);
	while(1);
	return 0;
}
