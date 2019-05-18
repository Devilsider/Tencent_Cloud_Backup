#include <func.h>
int main(){
	int semid=semget(1000,0,0600|IPC_CREAT);
	ERROR_CHECK(semid,-1,"semget");
	int ret=semctl(semid,IPC_RMID,0);
	ERROR_CHECK(ret,-1,"semctl");
	return 0;
}
