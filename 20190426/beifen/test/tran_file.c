#include "function.h"
int tranFile(int newFd){
	Train_t train;
	//发送文件名字	
	train.dataLen=strlen(FILENAME);
	strcpy(train.buf,FILENAME);
	send(newFd,&train,4+train.dataLen,0);
    int fd=open(FILENAME,O_RDONLY);
    ERROR_CHECK(fd,-1,"open");
    //文件大小
    struct stat buf;
    fstat(fd,&buf);
    train.dataLen=sizeof(buf.st_size);
    memcpy(train.buf,&buf.st_size,train.dataLen);
    int ret=send(newFd,&train,train.dataLen+4,0);
    ERROR_CHECK(ret,-1,"send");
    //发送文件内容
	while((train.dataLen=read(fd,train.buf,sizeof(train.buf)))){
		ret=send(newFd,&train,4+train.dataLen,0);	
        ERROR_CHECK(ret,-1,"send");
	}
	//发送文件结束标志
	send(newFd,&train,4,0);
	close(fd);
	return 0;
}
