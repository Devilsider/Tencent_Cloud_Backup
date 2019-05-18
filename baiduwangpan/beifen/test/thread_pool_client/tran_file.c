#include "function.h"
#define maxsize 104857600
#define maxMemorySize 2147483648
int tranFile(int newFd,char path[],pUsr_t pusr)
{
    fileInfo_t fileInfo;
    bzero(&fileInfo,sizeof(fileInfo_t));
    strcpy(fileInfo.fileName,path);
    Compute_file_md5(path,fileInfo.md5sum);
    Train_t train;
    bzero(&train,sizeof(train));
    //因为是虚拟目录设计,文件路径就存储为用户名
    strcpy(fileInfo.filePath,pusr->name);
    fileInfo.precode=pusr->precode;
    //先发文件名字信息结构体
    train.dataLen=sizeof(fileInfo_t);
    memcpy(train.buf,&fileInfo,sizeof(fileInfo_t));
    int ret=send(newFd,&train.dataLen,4,0);
    ERROR_CHECK(ret,0,"send");
    ret=send(newFd,train.buf,train.dataLen,0);
    ERROR_CHECK(ret,0,"send");
    
    //接收客户端传来的文件信息，存储为文件偏移量
    int dataLen;
    off_t offset;
    bzero(&train,sizeof(Train_t));
    recvCycle(newFd,&train.dataLen,4);
    recvCycle(newFd,train.buf,train.dataLen) ;
    memcpy(&offset,train.buf,train.dataLen);
    printf("offset is %ld\n",offset) ;
    //再发送文件大小
    int fd=open(path,O_RDONLY);
    ERROR_CHECK(fd,-1,"open");
    struct stat buf;
    bzero(&buf,sizeof(buf));
    fstat(fd,&buf);
    //printf("buf.st_size=%ld\n",buf.st_size);
    bzero(&train,sizeof(Train_t));
    train.dataLen=sizeof(buf.st_size);
    memcpy(train.buf,&buf.st_size,train.dataLen);
    //printf("train.buf=%s,train.dataLen=%d\n",train.buf,train.dataLen) ;
    ret=send(newFd,&train.dataLen,4,0);
    //printf("send ret = %d\n",ret);
    ERROR_CHECK(ret,-1,"send");
    ret=send(newFd,train.buf,train.dataLen,0);
    //printf("send ret=%d\n",ret);
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
            bzero(&train,sizeof(train));
            ret=send(newFd,&train,4,0);
            ERROR_CHECK(ret,-1,"send");
    }
    else{
        printf("int pages\n");
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
            ret=send(newFd,pStart,buf.st_size-upSize,0);
            ERROR_CHECK(ret,-1,"send");
            munmap(pStart,buf.st_size-upSize);
            upSize=upSize+ret;
            //发送文件结束标志
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

