#include <func.h>
#define N 10000000
typedef struct {
	pthread_mutex_t mutex;
	int num;
}Data;
void *threadFunc(void *p){
	Data *da=(Data *)p;
	for(int idx=0;idx<N;++idx){
		pthread_mutex_lock(&da->mutex);
		++da->num;
		pthread_mutex_unlock(&da->mutex);
	}
	pthread_exit(NULL);
}
int main(){
	Data da;
	da.num=0;

	int ret=pthread_mutex_init(&da.mutex,NULL);
	THREAD_ERROR_CHECK(ret,"pthread_mutex_init");

	pthread_t pthID;
	ret=pthread_create(&pthID,NULL,threadFunc,&da);
	THREAD_ERROR_CHECK(ret,"pthread_create");
	for(int idx=0;idx<N;++idx){
		pthread_mutex_lock(&da.mutex);
		++da.num;
		pthread_mutex_unlock(&da.mutex);	
	}
	ret=pthread_join(pthID,NULL);
	THREAD_ERROR_CHECK(ret,"pthread_join");
	printf("the result is %d.\n",da.num);
	ret = pthread_mutex_destroy(&da.mutex);
	THREAD_ERROR_CHECK(ret,"pthread_mutex_destory");
	return 0;

}
