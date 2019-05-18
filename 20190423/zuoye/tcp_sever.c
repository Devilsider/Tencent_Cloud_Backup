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
		
		int reuse=1;		
		int check;
		check=setsockopt(socketFd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));		
		ERROR_CHECK(check,-1,"setsockopt");	
		int ret;
		ret=bind(socketFd,(struct sockaddr *)&ser,sizeof(ser));
		ERROR_CHECK(ret,-1,"bind");
		ret=listen(socketFd,10);
		ERROR_CHECK(ret,-1,"listen");

		int new_fd;
		struct sockaddr_in client;
		bzero(&client,sizeof(client));
		int addrlen=sizeof(client);
		char buf[256];
	
		fd_set rdset;
		fd_set monitorSet;
		FD_ZERO(&rdset);
		FD_ZERO(&monitorSet);
		FD_SET(STDIN_FILENO,&monitorSet);
		FD_SET(socketFd,&monitorSet);
/*		int readyFdNum;	
		int epfd=epoll_create(1);
		ERROR_CHECK(epfd,-1,"epoll_create");
		struct epoll_event events,evs[2];
		events.events=EPOLLIN;
		events.data.fd=STDIN_FILENO;
		ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&events);
		ERROR_CHECK(ret,-1,"epoll_ctl");
		events.data.fd=new_fd;
		ret=epoll_ctl(epfd,EPOLL_CTL_ADD,new_fd,&events);
		ERROR_CHECK(ret,-1,"epoll_ctl");	
		int idx=0;
*/
		while(1){
				memcpy(&rdset,&monitorSet,sizeof(fd_set));	
				ret=select(11,&rdset,NULL,NULL,NULL);
				if(FD_ISSET(socketFd,&rdset)){	
					new_fd=accept(socketFd,(struct sockaddr*)&client,&addrlen);
					ERROR_CHECK(new_fd,-1,"accept");
					printf("client ip:%s,port:%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
					FD_SET(new_fd,&monitorSet);	
				}
				if(FD_ISSET(new_fd,&rdset)){	
					bzero(buf,sizeof(buf));
					ret=recv(new_fd,buf,sizeof(buf),0);
					ERROR_CHECK(ret,-1,"recv");
					if(0==ret){
						printf("Bye Bye:)\n");
						FD_CLR(new_fd,&monitorSet);
						close(new_fd);	
						continue;	
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
		close(socketFd);
		return 0;

}
