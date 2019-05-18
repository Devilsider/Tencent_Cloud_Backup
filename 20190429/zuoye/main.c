#include "function.h"

int main(int argc,char *argv[])
{   
    ARGS_CHECK(argc,5);
    Factory_t factory;
    int threadNum=atoi(argv[3]);
    int capacity=atoi(argv[4]);
    factoryInit(&factory,threadNum,capacity);
    factoryStart(&factory);
    int socketFd;
    tcpInit(&socketFd,argv[1],argv[2]);
    int newFd;
    pQue_t pq=&factory.que;
    while(1){
        newFd=accept(socketFd,NULL,NULL);
        ERROR_CHECK(newFd,-1,"accept");
        pNode_t pnew=(pNode_t)calloc(1,sizeof(Node_t));
        pnew->new_fd=newFd;
        pthread_mutex_lock(&pq->mutex);
        queInsert(pq,pnew);
        pthread_mutex_unlock(&pq->mutex);
        pthread_cond_signal(&factory.cond);
    }
    return 0;
}

