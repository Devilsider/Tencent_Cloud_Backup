#include <func.h>
int main(int argc,char *argv[]){
	ARGS_CHECK(argc,3);
	
	//初始化socket
	int socketFd;
	socketFd=socket(AF_INET,SOCK_STREAM,0);
	ERROR_CHECK(socketFd,-1,"socket");

	//初始化端口地址
	struct sockaddr_in client;
	bzero(&client,sizeof(client));
	client.sin_family=AF_INET;
	client.sin_port=htons(atoi(argv[2]));//参数2为端口号，主机字节序转换为网络字节序
	client.sin_addr.s_addr=inet_addr(argv[1]);//参数1为IP地址，点分十进制的主机字节序地址转换为32位二进制的网络字节序地址

	//初始化connect函数
	int ret;
	ret=connect(socketFd,(struct sockaddr*)&client,sizeof(client));
	ERROR_CHECK(ret,-1,"connect");
	printf("connect success :)\n");

	//准备发送
	ret=send(socketFd,"hello",5,0);
	ERROR_CHECK(ret,-1,"send");

	//准备接收
	char buf[128]={0};
	ret=recv(socketFd,buf,sizeof(buf),0);
	ERROR_CHECK(ret,-1,"recv");
	printf("I am client,gets :%s\n",buf);
	close(socketFd);
	return 0;
}
