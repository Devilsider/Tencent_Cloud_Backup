#include <func.h>
int main(int argc,char*argv[]){
	ARGS_CHECK(argc,3);
	
	//套接口初始化	
	int socketFd;
	socketFd=socket(AF_INET,SOCK_STREAM,0);
	ERROR_CHECK(socketFd,-1,"socket");
	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));	
	ser.sin_family=AF_INET;//IPV4
	ser.sin_port=htons(atoi(argv[2]));//参数2为端口号,从主机字节序转为网络字节序
	ser.sin_addr.s_addr=inet_addr(argv[1]);//地址转换，点分十进制转换为网络字节序，32位的二进制数

	//绑定端口号和IP地址
	int ret;
	ret=bind(socketFd,(struct sockaddr*)&ser,sizeof(ser));
	ERROR_CHECK(ret,-1,"bind");

	//监听端口listen
	ret=listen(socketFd,10);//使服务器这个端口和IP处于监听状态,最大连接请求为10
	ERROR_CHECK(ret,-1,"listen");
	
	//初始化accept，准备接受数据,产生新套接字
	int new_fd;
	struct sockaddr_in client;//初始化客户端地址信息
	bzero(&client,sizeof(client));
	int addrlen=sizeof(client);
	new_fd=accept(socketFd,(struct sockaddr*)&ser,&addrlen);
	ERROR_CHECK(ret,-1,"accept");
	printf("client ip=%s,port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
	
	//初始化recv函数，接收消息
	char buf[128]={0};
	ret=recv(new_fd,buf,sizeof(buf),0);
	ERROR_CHECK(ret,-1,"recv");
	printf("I am a sever,gets: %s\n",buf);
	
	//发送消息
	ret=send(new_fd,"world",5,0);
	ERROR_CHECK(ret,-1,"send");
	close(new_fd);
	close(socketFd);
	return 0;




}
