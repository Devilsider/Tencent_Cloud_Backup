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
	
	int epfd=epoll_create(1);
	ERROR_CHECK(epfd,-1,"epoll_create");
	struct epoll_event events,evs[2];
	events.events=EPOLLIN;
	events.data.fd=STDIN_FILENO;
	ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&events);
	ERROR_CHECK(ret,-1,"epoll_ctl");
	events.data.fd=socketFd;
	ret=epoll_ctl(epfd,EPOLL_CTL_ADD,socketFd,&events);
	ERROR_CHECK(ret,-1,"epoll_ctl");
	int idx=0;
	int readyFdNum;
		
	char buf[256];
	while(1){
		bzero(evs,sizeof(evs));
		readyFdNum=epoll_wait(epfd,evs,2,-1);	
		for(idx=0;idx<readyFdNum;++idx){
			if(evs[idx].data.fd==STDIN_FILENO){
				bzero(buf,sizeof(buf));	
				ret=read(STDIN_FILENO,buf,sizeof(buf));
				if(0==ret){
					printf("Bye Bye:)\n");
					goto chatover;	
				}	
				ret=send(socketFd,buf,strlen(buf)-1,0);
				ERROR_CHECK(ret,-1,"send");
			}	
			if(evs[idx].data.fd==socketFd){
				bzero(buf,sizeof(buf));
				ret=recv(socketFd,buf,sizeof(buf),0);
				ERROR_CHECK(ret,-1,"recv");
				if(0==ret){
					printf("Bye Bye!\n");
					goto chatover;	
				}	
				printf("I am client :),gets %s\n",buf);
			}
		}
	}
chatover:
	close(socketFd);
	return 0;	
}
