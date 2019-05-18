#include <func.h>
int main(int argc,char *argv[]){
		ARGS_CHECK(argc,3);		
		int socketFd;
		socketFd=socket(AF_INET,SOCK_STREAM,0);
		ERROR_CHECK(socketFd,-1,"socketFd");

		struct sockaddr_in ser;
		bzero(&ser,sizeof(ser));	
		ser.sin_family=AF_INET;
		ser.sin_port=htons(atoi(argv[2]));
		ser.sin_addr.s_addr=inet_addr(argv[1]);
		
		int ret;
		ret=bind(socketFd,(struct sockaddr *)&ser,sizeof(ser));
		ERROR_CHECK(ret,-1,"bind");
		ret=listen(socketFd,10);
		ERROR_CHECK(ret,-1,"listen");

		int new_fd;
		struct sockaddr_in client;
		bzero(&client,sizeof(client));
		int addrlen=sizeof(client);
		new_fd=accept(socketFd,(struct sockaddr *)&client,&addrlen);
		ERROR_CHECK(new_fd,-1,"accept");
		printf("client ip:%s,port:%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
		char buf[256];
	
		fd_set rdset;
		struct timeval t;
		while(1){	
			FD_ZERO(&rdset);
			FD_SET(STDIN_FILENO,&rdset);
			FD_SET(new_fd,&rdset);
			bzero(&t,sizeof(t));
			t.tv_sec=3;
			ret=select(new_fd+1,&rdset,NULL,NULL,&t);
			if(FD_ISSET(new_fd,&rdset)){	
				bzero(buf,sizeof(buf));
				ret=recv(new_fd,buf,sizeof(buf),0);
				ERROR_CHECK(ret,-1,"recv");
				if(0==ret){
					printf("Bye Bye:)\n");	
					break;	
				}	
				printf("I am server :),gets :%s\n",buf);
			}
			if(FD_ISSET(STDIN_FILENO,&rdset)){	
				bzero(buf,sizeof(buf));	
				ret=read(STDIN_FILENO,buf,sizeof(buf));
				if(0==ret){
					printf("Bye Bye :)\n");	
					break;	
				}	
				ERROR_CHECK(ret,-1,"read");	
				ret=send(new_fd,buf,strlen(buf)-1,0);
				ERROR_CHECK(ret,-1,"send");
			}
		}
		close(new_fd);
		close(socketFd);
		return 0;

}
