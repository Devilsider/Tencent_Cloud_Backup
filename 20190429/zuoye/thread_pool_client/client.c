#include "function.h"
#define slice 1000000
#define RECV_BLOCK 65536
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int socketFd;
    socketFd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    struct sockaddr_in ser;
    ser.sin_family=AF_INET;
    ser.sin_port=htons(atoi(argv[2]));
    ser.sin_addr.s_addr=inet_addr(argv[1]);
    int ret=connect(socketFd,(struct sockaddr*)&ser,sizeof(struct sockaddr_in));
    ERROR_CHECK(ret,-1,"connect");
    printf("connect success :)!\n");
    //先接收文件名
    int dataLen;
    char buf[4096];
    bzero(buf,sizeof(buf));
    ret=recvCycle(socketFd,&dataLen,4);
    ERROR_CHECK(ret,-1,"recv");
    ret=recvCycle(socketFd,buf,dataLen);
    ERROR_CHECK(ret,-1,"recv");
    printf("filename is %s\n",buf) ;
    //计算该文件大小,并将该文件大小传给服务器
    int fd=open(buf,O_RDWR|O_CREAT,0666);
    ERROR_CHECK(fd,-1,"open");  
    struct stat fileInfo;
    fstat(fd,&fileInfo);
    printf("the filesize is %f\n",(float)fileInfo.st_size) ;
    Train_t train;
    bzero(&train,sizeof(Train_t));
    train.dataLen=sizeof(fileInfo.st_size);
    memcpy(&train.buf,&fileInfo.st_size,train.dataLen);
    ret=send(socketFd,&train,train.dataLen+4,0);
    ERROR_CHECK(ret,-1,"send");
    //接收文件大小
    off_t filesize,sliceSize,downloadSize;
    ret=recvCycle(socketFd,&dataLen,4);
    ret=recvCycle(socketFd,&filesize,dataLen);
    printf("filesize is %f\n",(float)filesize);
    sliceSize=filesize/slice;
    downloadSize=0;
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
                ret=recvCycle(socketFd,&buf,dataLen);
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
        while(downloadSize+RECV_BLOCK<filesize){
            ret=splice(socketFd,NULL,fds1[1],NULL,RECV_BLOCK,SPLICE_F_MORE|SPLICE_F_NONBLOCK);
            ERROR_CHECK(ret,-1,"splice");
            ret=splice(fds1[0],NULL,fd,NULL,RECV_BLOCK,SPLICE_F_MORE|SPLICE_F_NONBLOCK);
            ERROR_CHECK(ret,-1,"splice");
            downloadSize+=ret;
            printf("\r%5.2f%%",(float)(downloadSize+fileInfo.st_size)/filesize*100);
            fflush(stdout);
        }
            ret=splice(socketFd,NULL,fds1[1],NULL,filesize-downloadSize,SPLICE_F_MORE|SPLICE_F_NONBLOCK);
            ERROR_CHECK(ret,-1,"splice");
            ret=splice(fds1[0],NULL,fd,NULL,ret,SPLICE_F_MORE|SPLICE_F_NONBLOCK);
            ERROR_CHECK(ret,-1,"splice");
            recvCycle(socketFd,&dataLen,4);
            printf("\r100%%     \n");
    }
end:
    close(fd);
    close(socketFd);
    return 0;
}

