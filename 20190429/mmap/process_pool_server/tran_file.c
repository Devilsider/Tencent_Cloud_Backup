#include "function.h"
#define maxsize 104857600
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
    lseek(fd,offset,SEEK_SET);
    //发送文件内容,根据偏移量发送文件，实现断点续传 
    if((buf.st_size-offset)<maxsize){
        while((train.dataLen=read(fd,train.buf,sizeof(train.buf)))){
                ret=send(newFd,&train,train.dataLen+4,0);
                ERROR_CHECK(ret,-1,"send");
          }
    }
    else{
       /* int pagesNum=0;
        pagesNum=(buf.st_size-offset-1)/4096+1;//向上取整
        int i;
        char *pStart;
        off_t total=offset;
        printf("pagesNum=%d\n",pagesNum) ;
        for(i=0;i<pagesNum;++i){
            //使用共享内存，将文件内容映射到内存
            pStart=(char *)mmap(NULL,4096,PROT_READ,MAP_SHARED,fd,0);
            ERROR_CHECK(pStart,NULL,"mmap");
            if((pagesNum-1)==i) {
                //最后一页
                printf("total = %f\n",(float)total);
                train.dataLen=buf.st_size-total;
                printf("train.dataLen = %f\n",(float)train.dataLen) ;
                memcpy(&train.buf,pStart,train.dataLen);
                ret=send(newFd,&train,train.dataLen+4,0);
                ERROR_CHECK(ret,-1,"send");
                munmap(pStart,4096);
            }
            else{
                train.dataLen=sizeof(train.buf);
                memcpy(&train.buf,pStart,train.dataLen);
                ret=send(newFd,&train,train.dataLen+4,0);
                ERROR_CHECK(ret,-1,"send");
                total=total+train.dataLen;
            }
            //一页读完，翻页
            lseek(fd,4096,SEEK_CUR);//不是最后一页
            munmap(pStart,4096);
        }
    }*/
        off_t total=offset;
        char *pStart;
        pStart=(char *)mmap(NULL,buf.st_size-offset,PROT_READ,MAP_SHARED,fd,0);
        ret=send(newFd,pStart,buf.st_size-offset,0);
        ERROR_CHECK(ret,-1,"send");
        //发送文件结束标志
        bzero(&train,sizeof(train));
        ret=send(newFd,&train,4,0);
        ERROR_CHECK(ret,-1,"send");
        close(fd);
    } 
    return 0;
}

