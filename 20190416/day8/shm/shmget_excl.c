#include <func.h>

int main()
{
	int shmid;
	shmid=shmget(1000,1024,0600|IPC_CREAT|IPC_EXCL);
	ERROR_CHECK(shmid,-1,"shmget");
	return 0;
}
