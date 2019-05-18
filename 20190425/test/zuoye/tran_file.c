#include "function.h"
int tranFile(int newFd){
	Train_t train;
	//发送文件名字	
	train.dataLen=strlen(FILENAME);
	strcpy(train.buf,FILENAME);
	int ret;
	ret=send(newFd,&train,4+train.dataLen,0);
	ERROR_CHECK(ret,-1,"send");
	int fd=open(FILENAME,O_RDONLY);
	ERROR_CHECK(fd,-1,"open");
	//发送文件内容
	while((train.dataLen=read(fd,train.buf,sizeof(train.buf)))){
		ret=send(newFd,&train,4+train.dataLen,0);	
		ERROR_CHECK(ret,-1,"send");
	}
	//发送文件结束标志
	send(newFd,&train,4,0);
	return 0;
}
