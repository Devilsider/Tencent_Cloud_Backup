#include <func.h>
#define	tickets 20000000
int main(){
	int shmid=shmget(1000,4096,0600|IPC_CREAT);	
	ERROR_CHECK(shmid,-1,"shmget");
	int *p=(int *)shmat(shmid,NULL,0);
	*p=tickets;
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
	int child_ticket=0;
	int parent_ticket=0;
	if(!fork()){
		printf("this is child process!\n");
		while(*p>0){		
			semop(semID,&sopp,1);
			*p=*p-1;
		 	++child_ticket;
			semop(semID,&sopv,1);	
		}
		printf("the tickets child bought :%d\n",child_ticket);	
	}
	else{
		printf("this is parent process!\n");
		while(*p>0){
			semop(semID,&sopp,1);
			++parent_ticket;	
			*p=*p-1;	
			semop(semID,&sopv,1);	
		}
		wait(NULL);
		printf("the remaining tickets:%d\n",*p);
		printf("the tickets parent bought :%d.\n",parent_ticket);	
		end=time(NULL);		
		printf("cost about %f seconds\n",difftime(end,start)); 	
		int ret;
		ret=shmctl(shmid,IPC_RMID,NULL);
		ERROR_CHECK(ret,-1,"shmctl");//清除共享内存
		shmctl(semID,IPC_RMID,0);//清除信号量
		return 0;
	}
}

