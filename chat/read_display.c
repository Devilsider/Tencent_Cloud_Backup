#include <func.h>
typedef struct{
	long mytype;
	char name[64];
	char buf[256];
}Data;
int main(){
	//打印显示数据
	//获取共享内存地址	
	int shmid=shmget(1000,4096,0600|IPC_CREAT);
	ERROR_CHECK(shmid,-1,"shmget");
	Data *p=(Data*)shmat(shmid,NULL,0);
	time_t now;

	//获取信号量集合
	int	semid=semget(1000,2,0600|IPC_CREAT);
   	ERROR_CHECK(semid,-1,"semget");
	struct sembuf sopp,sopv;
	sopp.sem_num=1;
	sopp.sem_op=-1;
	sopp.sem_flg=SEM_UNDO;
	sopv.sem_num=0;
	sopv.sem_op=1;
	sopv.sem_flg=SEM_UNDO;
	system("clear");
	Data da;
	while(1)
	{
		semop(semid,&sopp,1);
		memcpy(&da,p,sizeof(Data));
		memset(p,0,sizeof(Data));//读完后初始化内存
		if(0==da.mytype){
			now=time(NULL);
			printf("                          >>%s\n",ctime(&now));		
			printf("                          >>%s:%s\n",da.name,da.buf);		
		}
		else if(1==da.mytype){
			now=time(NULL);
			printf(">>%s\n",ctime(&now));
			printf(">>%s:%s\n",da.name,da.buf);	
		}
		else if(1000==da.mytype){
			//退出	
			break;	
		}
		else{
			printf("type error!\n");
			break;
		}
		semop(semid,&sopv,1);
	}
	int ret=shmctl(shmid,IPC_RMID,0);
	ERROR_CHECK(ret,-1,"shmctl");
	return 0;	
}
