#include <func.h>
#define n 10000000
int main(){
	int shmid=shmget(1000,4096,0600|IPC_CREAT);	
	ERROR_CHECK(shmid,-1,"shmget");
	int *p=(int *)shmat(shmid,NULL,0);
	*p=0;
	if(!fork()){
		printf("this is child process!\n");
		for(int idx=0;idx<n;++idx){
			*p=*p+1;	
		}
		return 0;	
	}
	else{
		printf("this is parent process!\n");
		for(int idx=0;idx<n;++idx){
			*p=*p+1;	
		}
		wait(NULL);	
		printf("res = %d\n",*p);
		int ret;
		ret=shmctl(shmid,IPC_RMID,NULL);
		ERROR_CHECK(ret,-1,"shmctl");
		return 0;
	}
}

