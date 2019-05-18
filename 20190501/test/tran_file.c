#include "function.h"
#define maxsize 104857600
#define maxMemorySize 2147483648
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
    //再发送文件大小
    int fd=open(FILENAME,O_RDONLY);
    ERROR_CHECK(fd,-1,"open");
    struct stat buf;
    bzero(&buf,sizeof(buf));
    fstat(fd,&buf);
    train.dataLen=sizeof(buf.st_size);
    memcpy(train.buf,&buf.st_size,train.dataLen);
    ret=send(newFd,&train,train.dataLen+4,0);
    ERROR_CHECK(ret,-1,"send");
    //根据客户端发来的信息，偏移offset在发送文件后续内容
    //lseek(fd,offset,SEEK_SET);
    off_t upSize=offset;       
    //发送文件内容,根据偏移量发送文件，实现断点续传 
    if((buf.st_size-offset)<maxsize){
        while((train.dataLen=read(fd,train.buf,sizeof(train.buf)))){
                ret=send(newFd,&train,train.dataLen+4,0);
                ERROR_CHECK(ret,-1,"send");
          }
    }
    else{
        int pages;
        pages=(buf.st_size-1)/maxMemorySize+1;
        char *pStart;
        int k;
        for( k=0;k<pages-1;++k){
            lseek(fd,upSize,SEEK_SET);
            pStart=(char *)mmap(NULL,buf.st_size-offset-k*maxMemorySize,PROT_READ,MAP_SHARED,fd,0);
            ret=send(newFd,pStart,buf.st_size-offset-k*maxMemorySize,0);
            ERROR_CHECK(ret,-1,"send");
            upSize=upSize+ret;
            //发送文件结束标志
            munmap(pStart,buf.st_size-offset-k*maxMemorySize);
        }
            pStart=(char *)mmap(NULL,buf.st_size-upSize,PROT_READ,MAP_SHARED,fd,0);
            printf("newFd=%d\n",newFd);
            printf("1111\n") ;
            ret=send(newFd,pStart,buf.st_size-upSize,0);
            ERROR_CHECK(ret,-1,"send");
            munmap(pStart,buf.st_size-upSize);
            upSize=upSize+ret;
            //发送文件结束标志
            printf("newFd=%d\n",newFd);
            bzero(&train,sizeof(train));
            ret=send(newFd,&train,4,0);
            ERROR_CHECK(ret,-1,"send");

        /*     
        ret=sendfile(newFd,fd,&upSize,buf.st_size-offset);
        upSize=upSize+ret;
        ERROR_CHECK(ret,-1,"sendfile");
         
    */ 
    }
    printf("upSize=%ld,buf.st_size=%ld",upSize,buf.st_size);
    bzero(&train,sizeof(Train_t));
    if(upSize==buf.st_size) {
        ret=send(newFd,&train,4,0);
        ERROR_CHECK(ret,-1,"send");
    }
    close(fd);
    return 0;
}

