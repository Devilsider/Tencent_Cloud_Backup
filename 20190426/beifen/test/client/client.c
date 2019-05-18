#include "function.h"
#define slice 10000000
int main(int argc,char *argv[]){
	ARGS_CHECK(argc,3);
	int socketFd;
	socketFd=socket(AF_INET,SOCK_STREAM,0);
	ERROR_CHECK(socketFd,-1,"socket");
	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));
	ser.sin_addr.s_addr=inet_addr(argv[1]);
	int ret;
	ret=connect(socketFd,(struct sockaddr *)&ser,sizeof(struct sockaddr_in));
	ERROR_CHECK(ret,-1,"connect");
	printf("connect success :)\n");
	int dataLen;
	char buf[1000];
	bzero(buf,sizeof(buf));
    ret=recvCycle(socketFd,&dataLen,4);
    ERROR_CHECK(ret,-1,"recvCycle");
    ret=recvCycle(socketFd,buf,dataLen);
    ERROR_CHECK(ret,-1,"recvCycle");
    int fd;
	fd=open(buf,O_CREAT|O_WRONLY,0666);
	ERROR_CHECK(fd,-1,"open");
    //接收文件大小
    off_t filesize=0,downLoadSize=0,sliceSize;//oldsize;
    ret=recvCycle(socketFd,&dataLen,4);
    ERROR_CHECK(ret,-1,"recvCycle");
    ret=recvCycle(socketFd,&filesize,dataLen);
    ERROR_CHECK(ret,-1,"recvCycle");
    sliceSize=filesize/slice;
	while(1){
		ret=recvCycle(socketFd,&dataLen,4);
        if(-1==ret)	{
            printf("server is update\n");
            break;
        }
        if(dataLen>0){
			ret=recvCycle(socketFd,buf,dataLen);
            if(-1==ret) {
                break;
            }
            write(fd,buf,dataLen);	
            downLoadSize+=dataLen;
           /* if((downLoadSize-oldsize)>sliceSize){
                printf("\r%5.2f%%",(float)downLoadSize/filesize*100);
                fflush(stdout);
                oldsize=downLoadSize;
            }*/
            if(dataLen>sliceSize){
                printf("\r%5.2f%%",(float)downLoadSize/filesize*100);
            }
            else{
                printf("\r100%%       \n");
            }
		}else{
			break;	
		}	
	}	
	close(fd);
	close(socketFd);
	return 0;
}
