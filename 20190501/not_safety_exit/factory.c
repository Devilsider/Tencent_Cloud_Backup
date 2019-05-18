#include "function.h"
void cleanup(void *p){
    pQue_t pq=(pQue_t)p;
    pthread_mutex_unlock(&pq->mutex);
    printf("I am cleanup!\n");
}
void *sigFunc(void *p)
{
    //判断队列是否为空，为空就睡觉
    pFactory_t pf=(pFactory_t)p;
    pQue_t pq=&pf->que;
    //pthread_cleanup_push(cleanup,&pf->que);
    pNode_t pcur;
    int getSuccess;
    while(1){
        pthread_mutex_lock(&pq->mutex);
        if(!pq->queSize){
            pthread_cond_wait(&pf->cond,&pq->mutex);
        }
        getSuccess=queGet(pq,&pcur);
        pthread_mutex_unlock(&pq->mutex);   
       if(!getSuccess){
            printf("I am thread,strat transfering:)\n");
            tranFile(pcur->new_fd);
            printf("transfer success!\n") ;
            free(pcur);
        }
    }
    //pthread_cleanup_pop(1);
}

void factoryInit(pFactory_t pf,int threadNum,int capacity){
    bzero(pf,sizeof(Factory_t));
    pf->pthid=(pthread_t *)calloc(threadNum,sizeof(pthread_t));
    pf->threadNum=threadNum;
    pthread_cond_init(&pf->cond,NULL);
    queInit(&pf->que,capacity);
}
void factoryStart(pFactory_t pf){
    int i;
    if(0==pf->startFlag){
        for(i=0;i<pf->threadNum;++i){ 
            pthread_create(pf->pthid+i,NULL,sigFunc,pf);
        }
        pf->startFlag=1;
    }
}
