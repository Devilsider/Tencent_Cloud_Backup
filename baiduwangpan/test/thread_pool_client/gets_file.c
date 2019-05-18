#include "function.h"
#define slice 1000000
#define RECV_BLOCK 65536
int clientTranFile(int socketFd,char path[],pUsr_t pusr)
{
        
    
    //先发送文件结构体
    Train_t train;
    fileInfo_t fileData; 
    pVirtualDir_t pvd; 
    pvd=(pVirtualDir_t)calloc(1,sizeof(virtualDir_t));
    int ret; 
    int dataLen;
    char buf[1000];
    bzero(&fileData,sizeof(fileInfo_t));
    bzero(&train,sizeof(Train_t));
    
    // 计算文件大小，一次都发过去
    int fd=open(path,O_RDWR|O_CREAT,0666);
    ERROR_CHECK(fd,-1,"open");
    struct stat fileInfo;
    fstat(fd,&fileInfo);
    printf("the fileInfo.filesize is %ld\n",fileInfo.st_size);
    fileData.fileSize=fileInfo.st_size;
    strcpy(fileData.fileName,path);
    strcpy(fileData.filePath,pusr->name);
   
    
    train.dataLen=sizeof(fileInfo_t);
    memcpy(train.buf,&fileData,sizeof(fileInfo_t));
    ret=send(socketFd,&train.dataLen,4,0);
    ERROR_CHECK(ret,-1,"send");
    ret=send(socketFd,train.buf,train.dataLen,0);
    ERROR_CHECK(ret,-1,"send");
    //再发送用户数据结构体
    
    
    
    
    //接收文件大小
    off_t filesize,sliceSize,downloadSize;
    bzero(&train,sizeof(Train_t));
    dataLen=0;
    filesize=0;
    ret=recvCycle(socketFd,&train.dataLen,4);
    printf("train.dataLen is %d\n",train.dataLen);
    ret=recvCycle(socketFd,train.buf,train.dataLen);
    printf("train.buf is %s,ret=%d\n",train.buf,ret);
//    ret=recvCycle(socketFd,&dataLen,4);
 //   ret=recvCycle(socketFd,buf,train.dataLen);
    bzero(&filesize,sizeof(off_t));
    memcpy(&filesize,train.buf,train.dataLen);
    printf("recv  filesize is %ld\n",filesize);
    sliceSize=filesize/slice;
    downloadSize=0;
    //20190508
    
    //filesize=90;
    //偏移到文件末尾开始写
    lseek(fd,fileInfo.st_size,SEEK_SET);
    if(fileInfo.st_size==filesize){
        printf("the file already exists!\n");
        goto end;
    }
    if((filesize-fileInfo.st_size)<104857600){
        while(1){
            ret=recvCycle(socketFd,&dataLen,4);
            if(-1==ret){
                printf("the server is updating \n");
                break;
            }
            if(dataLen>0){
                ret=recvCycle(socketFd,buf,dataLen);
                ret=write(fd,buf,dataLen);
                ERROR_CHECK(ret,-1,"write");
                downloadSize+=dataLen;
                if(dataLen>sliceSize){
                    printf("\r%5.2f%%",(float)(downloadSize+fileInfo.st_size)/filesize*100);
                    fflush(stdout);
                }else{
                    printf("\r100%%       \n");
                }
            }
            else{
                break;
            }
        }
     }
    else{
        //设定文件大小
       /* ftruncate(fd,filesize);
        char *pStart=(char *)mmap(NULL,filesize-fileInfo.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
        printf("pStart=%s\n",pStart) ;
        ret=recvCycle(socketFd,pStart,filesize-fileInfo.st_size);
        ERROR_CHECK(ret,-1,"recvCycle");
        munmap(pStart,filesize-fileInfo.st_size);
        */
        int fds1[2];
        pipe(fds1);
        int recvNum;
       // printf("dawn=%f,RECV_BLOCK=%f,filesize=%f,fileInfo.size_t=%f\n"
       //        ,(float)downloadSize,(float)RECV_BLOCK,(float)filesize,(float)fileInfo.st_size);
        while(downloadSize+RECV_BLOCK<filesize-fileInfo.st_size){
            recvNum=splice(socketFd,NULL,fds1[1],NULL,RECV_BLOCK,SPLICE_F_MORE|SPLICE_F_NONBLOCK);
            ERROR_CHECK(recvNum,-1,"splice");
            ret=splice(fds1[0],NULL,fd,NULL,RECV_BLOCK,SPLICE_F_MORE|SPLICE_F_NONBLOCK);
            ERROR_CHECK(ret,-1,"splice");
            downloadSize+=ret;
            printf("\r%5.2f%%",(float)(downloadSize+fileInfo.st_size)/filesize*100);
            fflush(stdout);
        }
        //    printf("dawn=%f,RECV_BLOCK=%f,filesize=%f,fileInfo.size_t=%f\n"
         //      ,(float)downloadSize,(float)RECV_BLOCK,(float)filesize,(float)fileInfo.st_size);
            recvNum=splice(socketFd,NULL,fds1[1],NULL,filesize-downloadSize-fileInfo.st_size,SPLICE_F_MORE|SPLICE_F_NONBLOCK);
            ERROR_CHECK(recvNum,-1,"splice");
            ret=splice(fds1[0],NULL,fd,NULL,recvNum,SPLICE_F_MORE|SPLICE_F_NONBLOCK);
            ERROR_CHECK(ret,-1,"splice");
            close(fds1[1]);
            close(fds1[0]);
            ret=recvCycle(socketFd,&dataLen,4);
            ERROR_CHECK(ret,-1,"recvCycle");
            printf("\r100%%     \n");
    }
end:
    close(fd);
    close(socketFd);
    return 0;
}

