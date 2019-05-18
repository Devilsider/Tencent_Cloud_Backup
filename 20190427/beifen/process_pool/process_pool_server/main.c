#include "function.h"
int exitFds[2];
void sigFunc(int sigNum){
    write(exitFds[1],&sigNum,1);
}

int main(int argc,char *argv[])
{
    while(fork()){
        int status;
        wait(&status);
        if(WIFEXITED(status)){
            printf("normal exit!\n");
            exit(0);
        }
    }
    ARGS_CHECK(argc,4);

    pipe(exitFds);
    signal(SIGUSR1,sigFunc);

    int childNum=atoi(argv[3]);
    Process_Data *pChild=(Process_Data *)calloc(childNum,sizeof(Process_Data));
    makeChild(pChild,childNum);
    int socketFd;
    tcpInit(&socketFd,argv[1],argv[2]) ;
    int epfd=epoll_create(1);
    ERROR_CHECK(epfd,-1,"epoll_create");
    struct epoll_event event,*evs;
    evs=(struct epoll_event *)calloc(childNum+2,sizeof(struct epoll_event));
    event.events=EPOLLIN;
    event.data.fd=socketFd;
    int ret=epoll_ctl(epfd,EPOLL_CTL_ADD,socketFd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    int i;
    for(i=0;i<childNum;++i){
        event.data.fd=pChild[i].fd;
        ret=epoll_ctl(epfd,EPOLL_CTL_ADD,pChild[i].fd,&event);
        ERROR_CHECK(ret,-1,"epoll_ctl");
    }

    //添加退出机制
    event.data.fd=exitFds[0];
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,exitFds[0],&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    
    int j;
    int readyFdNum;
    int newFd;
    while(1){
        readyFdNum=epoll_wait(epfd,evs,childNum+2,-1);
        for(i=0;i<readyFdNum;++i){
            if(evs[i].events==EPOLLIN&&evs[i].data.fd==socketFd)
            {
                newFd=accept(socketFd,NULL,NULL);
                ERROR_CHECK(newFd,-1,"accept");
                for(j=0;j<childNum;++j){
                    if(!pChild[j].busy){
                        sendFd(pChild[j].fd,newFd,1); //发送newFd,子进程开始向客户端发送文件
                        pChild[j].busy=1;
                        printf("child %d is busy.\n",pChild[j].pid);
                        break; 
                    }
                }
                close(newFd);
            }
            if(evs[i].events==EPOLLIN&&evs[i].data.fd==exitFds[0]){
                printf("start exit!:)\n");
                close(socketFd);
                for(j=0;j<childNum;++j){
                    sendFd(pChild[j].fd,0,0);
                }
                for(j=0;j<childNum;++j){
                    wait(NULL);
                }
                return 0;
            }
            for(j=0;j<childNum;++j)
            {
                if(evs[j].data.fd==pChild[j].fd){
                    read(pChild[j].fd,&ret,1);
                    pChild[j].busy=0;
                    printf("child %d isn't busy.\n",pChild[j].pid);
                }
            }
        }
    } 
    return 0;
}

