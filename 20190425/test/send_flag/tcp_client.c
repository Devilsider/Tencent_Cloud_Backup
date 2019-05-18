#include <func.h>
#define N 1048576
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
	ret=connect(socketFd,(struct sockaddr*)&ser,sizeof(ser));	
	ERROR_CHECK(ret,-1,"connect");	
	printf("connect sucess!\n");	
	int count;
	for(int idx=0;idx<N;++idx){
		ret=send(socketFd,"hello",5,0);
		count=count+ret;	
		printf("%d\n",count);
		if(0==ret){
			printf("buff is full!\n");	
		}
	}	
	return 0;
}
