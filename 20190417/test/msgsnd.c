#include <func.h>
typedef struct msgbuf{
	long mytype;
	char mtext[64];
}
int main(int argc,char *argv[]){
	ARGS_CHECK(argc,3);
	int msgid=msgget(1000,0600|IPC_CREAT);
	ERROR_CHECK(msgid,-1,"msgget");
	
}

