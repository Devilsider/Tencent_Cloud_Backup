#include <func.h>
int main(){
	int shmid = shmget(1000,4096,0600|IPC_CREAT);
	ERROR_CHECK(shmid,-1,"shmget");	
	char *pShm=(char *)shmat(shmid,NULL,0);
	char buf[256];
	memset(buf,'\0',sizeof(buf));
	if(!fork()){
		printf("this is child process!\n");
		strcpy(pShm,"How are you?\n");
		return 0;	
	}	
	else{
		wait(NULL);	
		printf("this is parent process!\n");
		strcpy(buf,pShm);
		puts(buf);
		int ret=shmctl(shmid,IPC_RMID,NULL);
		ERROR_CHECK(ret,-1,"shmctl");	
		return 0;	
	}
}
