#include "function.h"
int exitFds[2];
void sigfunc(int signum){
    write(exitFds[1],&signum,1);
}
int main(int argc,char *argv[]){
    while(fork()){//若进程因为异常退出后重新将其拉起来
        int status;
        wait(&status);
        if(WIFEXITED(status))
        {
            printf("exit normally!\n");
            exit(0);
        }
    }
    ARGS_CHECK(argc,4);
    
    pipe(exitFds);
    signal(SIGUSR1,sigfunc);

	int childNum=atoi(argv[3]);
	Process_Data *pChild=(Process_Data *)calloc(childNum,sizeof(Process_Data));
	makeChild(pChild,childNum);	
	int socketFd;
	tcpInit(&socketFd,argv[1],argv[2]);
	int epfd;
	epfd=epoll_create(1);
	ERROR_CHECK(epfd,-1,"epoll_create");
	struct epoll_event event,*evs;
	event.events=EPOLLIN;
	event.data.fd=socketFd;
	evs=(struct epoll_event *)calloc(childNum+1,sizeof(struct epoll_event));
	int ret;
	ret=epoll_ctl(epfd,EPOLL_CTL_ADD,socketFd,&event);	
	ERROR_CHECK(ret,-1,"epoll_ctl");
	int i;
	for(i=0;i<childNum;++i){
		event.data.fd=pChild[i].fd;
		ret=epoll_ctl(epfd,EPOLL_CTL_ADD,pChild[i].fd,&event);		
		ERROR_CHECK(ret,-1,"epoll_ctl");	
	}
    //添加退出机制
    event.data.fd=exitFds[0];
    epoll_ctl(epfd,EPOLL_CTL_ADD,exitFds[0],&event); 
    
    int readyFdNum;	
	int j;
	int newFd;
	while(1){
		readyFdNum=epoll_wait(epfd,evs,childNum+1,-1);
		for(i=0;i<readyFdNum;++i){
			if(evs[i].events==EPOLLIN&&evs[i].data.fd==socketFd){
				newFd=accept(socketFd,NULL,NULL);
                ERROR_CHECK(newFd,-1,"accept");
				for(j=0;j<childNum;++j){
					if(!pChild[j].busy){
						//发送newFd
						sendFd(pChild[j].fd,newFd,1);	
						pChild[j].busy=1;
						printf("child %d is busy!\n",pChild[j].pid);
						break;	
					}	
				}	
				close(newFd);
			}	
            if(evs[i].events==EPOLLIN&&evs[i].data.fd==exitFds[0]){
                printf("start exit!\n");
                close(socketFd);
                for(j=0;j<childNum;++j){
                    sendFd(pChild[j].fd,0,0);
                }
                for(j=0;j<childNum;++j){
                    wait(NULL);
                }
                return 0;
            }
			for(j=0;j<childNum;++j){
				if(evs[j].data.fd==pChild[j].fd){
					read(pChild[j].fd,&ret,1);
					pChild[j].busy=0;
					printf("child %d is not busy\n",pChild[j].pid);
				}	
			}
		}
	}
	return 0;
}
