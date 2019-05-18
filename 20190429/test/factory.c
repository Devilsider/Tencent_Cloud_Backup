#include "function.h"
void *sigFunc(void *p){
    pFactory_t pf=(pFactory_t)p;
    pQue_t pq=&pf->que; 
    pNode_t pcur;
    int ret;
    while(1){
        pthread_mutex_lock(&pq->mutex);
        if(!pq->queSize){
            pthread_cond_wait(&pf->cond,&pq->mutex);
        }
        ret=queGet(pq,&pcur);
        pthread_mutex_unlock(&pq->mutex);
        if(!ret){
            printf("I am thread!strat transferring ~ :)\n");
            tranFile(pcur->new_fd);
            printf("I finish,Quickly praise me:)\n");
            free(pcur);
        }
    }
}

void factoryInit(pFactory_t pf,int threadNum,int capacity)
{
    bzero(pf,sizeof(Factory_t));
    pf->pthid=(pthread_t *)calloc(threadNum,sizeof(pthread_t));
    pf->threadNum=threadNum;
    queInit(&pf->que,capacity);
    pthread_cond_init(&pf->cond,NULL);
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

