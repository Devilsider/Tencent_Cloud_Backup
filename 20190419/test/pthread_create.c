#include <func.h>
void* threadFunc(void *p){
	printf("I am child thread!\n");
	pthread_exit(NULL);	
}
int main(){
	pthread_t pthID;//线程ID
	int ret;
	ret = pthread_create(&pthID,NULL,threadFunc,NULL);
	THREAD_ERROR_CHECK(ret,"pthread_create");
	printf("I am main thread!\n");
	sleep(3);
	return 0;
}
