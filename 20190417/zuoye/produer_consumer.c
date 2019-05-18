#include <func.h>
int main(){
	//建立计数信号量
	int semArrID=semget(1000,2,0600|IPC_CREAT);
	ERROR_CHECK(semArrID,-1,"semget");
	unsigned short arr[2]={10,0};
	int ret;
	ret = semctl(semArrID,0,SETALL,arr);	
	ERROR_CHECK(ret,-1,"semctl");
	struct sembuf sopp,sopv;
	if(!fork()){
		sopp.sem_num=0;
		sopp.sem_op=-1;
		sopp.sem_flg=SEM_UNDO;
		sopv.sem_num=1;
		sopv.sem_op=1;
		sopv.sem_flg=SEM_UNDO;
		while(1)
		{
			printf("I am producer,products:%d,space:%d.\n",semctl(semArrID,1,GETVAL),semctl(semArrID,0,GETVAL));
			semop(semArrID,&sopp,1);
			printf("I will produce\n");
			semop(semArrID,&sopv,1);
			printf("I am producer,products:%d,space:%d.\n",semctl(semArrID,1,GETVAL),semctl(semArrID,0,GETVAL));
			sleep(1);	
		}
	return 0;	
	}
	else{
		sopp.sem_num=1;
		sopp.sem_op=-1;
		sopp.sem_flg=SEM_UNDO;
		sopv.sem_num=0;
		sopv.sem_op=1;
		sopv.sem_flg=SEM_UNDO;
		while(1){
			printf("I am consumer,products:%d,space:%d.\n",semctl(semArrID,1,GETVAL),semctl(semArrID,0,GETVAL));
			semop(semArrID,&sopp,1);
			printf("I will consume!\n");
			semop(semArrID,&sopv,1);
			printf("I am consumer,products:%d,space:%d.\n",semctl(semArrID,1,GETVAL),semctl(semArrID,0,GETVAL));
			sleep(2);	
		}
		wait(NULL);
		int ret=semctl(semArrID,IPC_RMID,0);
		ERROR_CHECK(ret,-1,"semctl");
		return 0;
	}
}
