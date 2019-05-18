#include <func.h>
#define n 10000000
int main(){
	int shmid=shmget(1000,4096,0600|IPC_CREAT);	
	ERROR_CHECK(shmid,-1,"shmget");
	int *p=(int *)shmat(shmid,NULL,0);
	*p=0;
	int semID=semget(1000,1,0600|IPC_CREAT); 
	ERROR_CHECK(semID,-1,"semget");
	int ret=semctl(semID,0,SETVAL,1);
	ERROR_CHECK(ret,-1,"semctl");
	struct sembuf sopp,sopv;
	time_t start,end;	
	sopp.sem_num=0;
	sopp.sem_op=-1;
	sopp.sem_flg=SEM_UNDO;
	sopv.sem_num=0;
	sopv.sem_op=1;
	sopv.sem_flg=SEM_UNDO;
	start=time(NULL);
	if(!fork()){
		printf("this is child process!\n");
		for(int idx=0;idx<n;++idx){
			semop(semID,&sopp,1);
			*p=*p+1;	
			semop(semID,&sopv,1);	
		}
		return 0;	
	}
	else{
		printf("this is parent process!\n");
		for(int idx=0;idx<n;++idx){
			semop(semID,&sopp,1);
			*p=*p+1;	
			semop(semID,&sopv,1);	
		}
		wait(NULL);
		end=time(NULL);	
		printf("res = %d\n",*p);
		printf("cost about %f seconds\n",difftime(end,start)); 	
		int ret;
		ret=shmctl(shmid,IPC_RMID,NULL);
		ERROR_CHECK(ret,-1,"shmctl");
		return 0;
	}
}

