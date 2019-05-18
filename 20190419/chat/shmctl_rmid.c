#include <func.h>
int main(){
	int shmid=shmget(1000,4096,0600|IPC_CREAT);
	ERROR_CHECK(shmid,-1,"shmget");
	int ret=shmctl(shmid,IPC_RMID,0);
	ERROR_CHECK(ret,-1,"shmctl");
	return 0;
}
