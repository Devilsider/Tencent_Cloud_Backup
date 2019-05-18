#include "function.h"
#define childNum 10
int tcpInit(int *pSocketFd,char *ip,char *port){
	int socketFd;
	socketFd=socket(AF_INET,SOCK_STREAM,0);
	ERROR_CHECK(socketFd,-1,"socket");
	struct sockaddr_in ser;
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(port));
	ser.sin_addr.s_addr=inet_addr(ip);
	int ret;
	ret=bind(socketFd,(struct sockaddr *)&ser,sizeof(sockaddr_in));
	ERROR_CHECK(ret,-1,"bind");
	listen(socketFd,childNum);	
	*pSocketFd=socketFd;
	return 0;
}
