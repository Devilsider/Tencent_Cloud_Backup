#include <func.h>
#define ticket_num 20000000
typedef struct{
	int tickets;
	pthread_mutex_t mutex;
}Train;
void *saleWindow1(void *p){
	Train *pSale=(Train *)p;
	int count = 0;
	while(1){
		pthread_mutex_lock(&pSale->mutex);
		if(pSale->tickets>0){
			--pSale->tickets;
			++count;
			pthread_mutex_unlock(&pSale->mutex);	
		}	
		else{
			pthread_mutex_unlock(&pSale->mutex);	
			printf("I am saleWindow1,I bought %d!\n",count);
			break;	
		}
	}	
	pthread_exit(NULL);
}

void *saleWindow2(void *p){
	Train *pSale=(Train *)p;
	int count = 0;
	while(1){
		pthread_mutex_lock(&pSale->mutex);
		if(pSale->tickets>0){
			--pSale->tickets;
			++count;
		pthread_mutex_unlock(&pSale->mutex);	
		}	
		else{
			pthread_mutex_unlock(&pSale->mutex);	
			printf("I am saleWindow2,I bought %d!\n",count);
			break;	
		}
	}	
	pthread_exit(NULL);
}
typedef void*(*threadFunc)(void *);
int main(){
	Train t;
	pthread_t pthId[2];
	int i;
	t.tickets=ticket_num;
	threadFunc pthreadFunc[2]={saleWindow1,saleWindow2};
	pthread_mutex_init(&t.mutex,NULL);
	for(i=0;i<2;++i){
		pthread_create(pthId+i,NULL,pthreadFunc[i],&t);
	}
	for(i=0;i<2;++i){
		pthread_join(pthId[i],NULL);
	}
	printf("sale over!\n");	
	return 0;
}
