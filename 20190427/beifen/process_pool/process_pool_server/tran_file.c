#include "function.h"
int tranFile(int newFd)
{
    Train_t train;
    bzero(&train,sizeof(train));
    //先发文件名字
    train.dataLen=strlen(FILENAME);
    strcpy(train.buf,FILENAME);
    int ret=send(newFd,&train,train.dataLen+4,0);
    ERROR_CHECK(ret,-1,"send");
    //接收客户端传来的文件信息，存储为文件偏移量
    int dataLen;
    off_t offset;
    recvCycle(newFd,&dataLen,4);
    recvCycle(newFd,&offset,dataLen) ;
    printf("the offset is %f\n",(float)offset);
    //再发送文件大小
    int fd=open(FILENAME,O_RDONLY);
    ERROR_CHECK(fd,-1,"open");
    struct stat buf;
    bzero(&buf,sizeof(buf));
    fstat(fd,&buf);
    train.dataLen=sizeof(buf.st_size);
    printf("filesize is train.dataLen %d\n",train.dataLen);
    memcpy(train.buf,&buf.st_size,train.dataLen);
    ret=send(newFd,&train,train.dataLen+4,0);
    ERROR_CHECK(ret,-1,"send");
    //根据客户端发来的信息，偏移offset在发送文件后续内容
    lseek(fd,offset,SEEK_SET);
    //发送文件内容,根据偏移量发送文件，实现断点续传
    while((train.dataLen=read(fd,train.buf,sizeof(train.buf)))){
           ret=send(newFd,&train,train.dataLen+4,0);
           ERROR_CHECK(ret,-1,"send");
    }
    //发送文件结束标志
    ret=send(newFd,&train,4,0);
    ERROR_CHECK(ret,-1,"send");
    close(fd);
    return 0;
}

