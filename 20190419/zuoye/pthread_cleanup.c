#include <func.h>
typedef struct {
	int num;
}Data;
void CleanFunc(void *p){
	Data *da=(Data *)p;
	printf("I am CleanFunc,I will free memeory!the num is %d\n",da->num);
	free(p);
}
void* threadFunc(void *p){
	char buf[128];
	bzero(buf,sizeof(buf));
	Data *da=(Data*)p;
	Data *newDa=(Data* )calloc(1,sizeof(Data));
	newDa->num=da->num;
	pthread_cleanup_push(CleanFunc,newDa);
	printf("I am child thread!I am reading!\n");
	read(STDIN_FILENO,buf,sizeof(buf));
	pthread_cleanup_pop(1);	
	pthread_exit(NULL);
}
int main(){
	Data da;
	da.num=1;
	pthread_t pthID;
	int ret =pthread_create(&pthID,NULL,threadFunc,&da);
	THREAD_ERROR_CHECK(ret,"pthread_create");
	printf("I am main thread!\n");
	ret=pthread_cancel(pthID);
	THREAD_ERROR_CHECK(ret,"pthread_cancel");
	ret=pthread_join(pthID,NULL);
	THREAD_ERROR_CHECK(ret,"pthread_join");
	return 0;	
}
