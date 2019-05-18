#include "function.h"
int exitFds[2];
void sigfunc(int sigNum){
    write(exitFds[1],&sigNum,1);
}

int main(int argc,char *argv[])
{   
    while(fork()){//生成子进程，子进程负责将new_fd加入队列，父进程只负责监听信号，通知各个子进程让各个子线程退出
        //若因为异常退出，重新将其拉起来
        int status;
        wait(&status);
        if(WIFEXITED(status)){
            printf("exit normally!\n");
            exit(0);
        }
        pipe(exitFds);
        signal(SIGUSR1,sigfunc);
    }


    ARGS_CHECK(argc,5);
    
   // pipe(exitFds);
    //signal(SIGUSR1,sigfunc);

    Factory_t factory;
    int threadNum=atoi(argv[3]);
    int capacity=atoi(argv[4]);
    factoryInit(&factory,threadNum,capacity);
    factoryStart(&factory);
    int socketFd;
    tcpInit(&socketFd,argv[1],argv[2]);
    int newFd;
    pQue_t pq=&factory.que;
    int ret;

    int epfd=epoll_create(1);
    ERROR_CHECK(epfd,-1,"epoll_create");
    struct epoll_event event,evs[2];
    event.events=EPOLLIN;
    event.data.fd=exitFds[0];
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,exitFds[0],&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    event.data.fd=socketFd;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,socketFd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    int i;
    int j;
    int readyFdNum;
    while(1){
        readyFdNum=epoll_wait(epfd,evs,2,-1);
        ERROR_CHECK(readyFdNum,-1,"epoll_wait");
        for(j=0;j<readyFdNum;++j) {
             if(evs[j].events==EPOLLIN&&evs[j].data.fd==socketFd) {
                newFd=accept(socketFd,NULL,NULL);
                ERROR_CHECK(newFd,-1,"accept");
                pNode_t pnew=(pNode_t)calloc(1,sizeof(Node_t));
                
                
                pnew->new_fd=newFd;
                pthread_mutex_lock(&pq->mutex);
                queInsert(pq,pnew);
                pthread_mutex_unlock(&pq->mutex);
                pthread_cond_signal(&factory.cond);
              }
            //退出机制 
            if(evs[j].events==EPOLLIN&&evs[j].data.fd==exitFds[0]){
                printf("start exit:)\n");
                close(socketFd);
                pthread_mutex_lock(&factory.mutex);
                factory.endFlag=1;
                pthread_mutex_unlock(&factory.mutex);
                pthread_cond_broadcast(&factory.cond);
                for(i=0;i<threadNum;++i){
                    pthread_cancel((factory.pthid[i]));//可能有问题
                }
                for(i=0;i<threadNum;++i){
                    pthread_join(factory.pthid[i],NULL);
                }
                printf("exit finish!\n");
            }
        }
    }
    return 0;
}

