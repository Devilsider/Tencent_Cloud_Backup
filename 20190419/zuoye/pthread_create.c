#include <func.h>
typedef struct {
	int num;
}Data;
void *threadFunc(void *p){
	Data *da=(Data *)p;
	Data *newDa=(Data *)calloc(1,sizeof(Data));//申请一个结构体newda,作为返回值
	newDa->num=da->num;
	printf("I am child thread!\n");
	printf("the num is %d\n",newDa->num); 
	newDa->num=3;
	pthread_exit(newDa);	
}
int main(){
	pthread_t pthID;
	Data da;
	da.num=2;
	void *rsv;
	int ret;
	ret=pthread_create(&pthID,NULL,threadFunc,&da);
	THREAD_ERROR_CHECK(ret,"pthread_create");
	pthread_join(pthID,&rsv);
	printf("I am parent thread!\n");
	printf("the num is %d\n",((Data *)rsv)->num);	
	free(rsv);	
	return 0;
}
