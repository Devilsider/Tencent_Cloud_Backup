#include <func.h>
#define type0 1 
#define type1 2
#define name0 "山本八十九"//自己的名字
#define name1 "龟田太郎"//对方的名字
/*
typedef struct {
	long mytype;
	char name[64];
	char buf[256];
}Data;*/

typedef struct msgbuf{
	//消息队列结构体
	long mytype;
	char mtext[64];
}MSG;

int main(){
	//B1端，显示来自B端的消息
	//使用消息队列接受来自B端的消息
	MSG rcvmsg;
	int ret;
	int msgID=msgget(1000,IPC_CREAT|0600);
	ERROR_CHECK(msgID,-1,"msgget");
	system("clear");
	while(1){
		ret=msgrcv(msgID,&rcvmsg,sizeof(rcvmsg.mtext),0,0);
		ERROR_CHECK(ret,-1,"rcvmsg");	
		if(type0==rcvmsg.mytype){
			//由自己发过来的消息
			printf("                          >>%s:%s\n",name0,rcvmsg.mtext);	
		}
		else if(type1==rcvmsg.mytype){
			//由对端发过来的消息
			printf(">>%s:%s\n",name1,rcvmsg.mtext);	
		}
		else {
			printf("error type!\n");
			break;	
		}
	}
	return 0;	
}
