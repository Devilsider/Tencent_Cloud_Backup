#include <func.h>
#define ticket 20000000
#define N 3
typedef struct{
	int tickets;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
}Data;
void *sellWindow1(void *p){
	int count=0;
	Data *da=(Data *)p;
	while(1){
		int ret=pthread_mutex_lock(&da->mutex);
		pTHREAD_ERROR_CHECK(ret,"pthread_mutex_lock");
		if(da->tickets>0){
//			printf("I am sellWindow1,:)now the remaining ticket is %d!\n",da->tickets);	
			--(da->tickets);
			if(0==(da->tickets)){
				//向setticket发送信号
				pthread_cond_signal(&da->cond);	
				pTHREAD_ERROR_CHECK(ret,"pthread_cond_signal");
			}
			++count;
//			printf(">>Finish,I am sellWindow1,:),now remain %d tickets!\n",da->tickets);
			ret=pthread_mutex_unlock(&da->mutex);
			pTHREAD_ERROR_CHECK(ret,"pthread_mutex_unlock");
		}
		else{
			ret=pthread_mutex_unlock(&da->mutex);
			pTHREAD_ERROR_CHECK(ret,"pthread_mutex_unlock");
			printf(">>Sale over,I am sellWindow1,get %d tickets!\n",count);	
			break;
		}	
//		sleep(1);	
	}
	pthread_exit(NULL);
}
void *sellWindow2(void *p){
	int count=0;
	Data *da=(Data *)p;
	while(1){
		int ret=pthread_mutex_lock(&da->mutex);
		pTHREAD_ERROR_CHECK(ret,"pthread_mutex_lock");
		if(da->tickets>0){
//			printf("I am sellWindow2,:) now the remianing tickets is %d!\n",da->tickets);	
			--(da->tickets);
			if(0==(da->tickets)){
				//向setticket发送信号
				ret=pthread_cond_signal(&da->cond);	
				pTHREAD_ERROR_CHECK(ret,"pthread_cond_signal");
			}
			++count;
//			printf(">>Finish,I am sellWindow2,:),now remain %d tickets!\n",da->tickets);
			ret=pthread_mutex_unlock(&da->mutex);
			pTHREAD_ERROR_CHECK(ret,"pthread_mutex_unlock");
		}
		else{
			ret=pthread_mutex_unlock(&da->mutex);
			pTHREAD_ERROR_CHECK(ret,"pthread_mutex_unlock");
			printf(">>Sale over,I am sellWindow2,get %d tickets!\n",count);	
			break;	
		}	
//		sleep(1);
	}
	pthread_exit(NULL);
}
void *setTickets(void *p){
	Data *da=(Data *)p;
	int ret = pthread_mutex_lock(&da->mutex);
	pTHREAD_ERROR_CHECK(ret,"pthread_mutex_lock");
	if(da->tickets>0){
		ret=pthread_cond_wait(&da->cond,&da->mutex);
		pTHREAD_ERROR_CHECK(ret,"pthread_cond_wait");		
	}
	da->tickets=ticket;
	ret=pthread_mutex_unlock(&da->mutex);
	pTHREAD_ERROR_CHECK(ret,"pthread_mutex_unlock");
	pthread_exit(NULL);
}
typedef void*(*threadFunc)(void *);
int main(){
	Data da;
	da.tickets=ticket;	
	//初始化互斥锁和同步条件
	int ret = pthread_mutex_init(&da.mutex,NULL);
	THREAD_ERROR_CHECK(ret,"pthread_mutex_init");
	ret=pthread_cond_init(&da.cond,NULL);
	THREAD_ERROR_CHECK(ret,"pthread_cond_t");
	//初始化函数指针
	threadFunc pthreadFunc[N]={sellWindow1,sellWindow2,setTickets};
	//初始化线程
	pthread_t pthID[N];
	for(int idx=0;idx<N;++idx){
		ret=pthread_create(pthID+idx,NULL,pthreadFunc[idx],&da);	
		THREAD_ERROR_CHECK(ret,"pthread_create");
	}
	for(int idx=0;idx<N;++idx){
		ret=pthread_join(pthID[idx],NULL);	
		THREAD_ERROR_CHECK(ret,"pthread_join");
	}
	printf("sell over!\n");
	//注销锁和条件变量
	ret=pthread_mutex_destroy(&da.mutex);
	THREAD_ERROR_CHECK(ret,"pthread_mutex_destroy");
	ret=pthread_cond_destroy(&da.cond);
	THREAD_ERROR_CHECK(ret,"pthread_cond_destroy");
	return 0;
}
