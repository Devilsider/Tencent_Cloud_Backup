#include "function.h"
#define slice 1000000
#define RECV_BLOCK 65536
int clientTranFile(int socketFd)
{
    //先接收文件结构体
    
    
    Train_t train;
    fileInfo_t fileData; 
    pVirtualDir_t pvd; 
    pvd=(pVirtualDir_t)calloc(1,sizeof(virtualDir_t));
    int ret; 
    int dataLen;
    char buf[1000];
    bzero(&train,sizeof(Train_t));
    ret=recvCycle(socketFd,&train.dataLen,4);
    ERROR_CHECK(ret,-1,"recv");
    ret=recvCycle(socketFd,train.buf,train.dataLen);
    ERROR_CHECK(ret,-1,"recv");
    memcpy(&fileData,train.buf,sizeof(fileInfo_t));
    printf("filename is %s,file path=%s,file md5sum is %s\n",fileData.fileName,fileData.filePath,fileData.md5sum) ;
    


    //将文件记录添加到数据库
    sqlData sd;
    bzero(&sd,sizeof(sqlData));
    strcpy(sd.sql_server,"localhost");
    strcpy(sd.sql_usr,"root");
    strcpy(sd.sql_password,"wow18771731658");
    strcpy(sd.sql_database,"baiduwangpan");

    bzero(sd.sql_command,sizeof(sd.sql_command));
    sprintf(sd.sql_command,"%s'%s',%d,'%s')","insert into usrOp (user,command,path) values("
              ,fileData.filePath,3,fileData.fileName);
   // printf("---3--%s\n",sd.sql_command);
    insertSql(&sd);

    //首先查看数据库有无相同文件，若有只增加记录，若无则上传
    //pernode 虚拟目录
    bzero(sd.sql_command,sizeof(sd.sql_command));
    sprintf(sd.sql_command,"%s'%s'","select precode,belongID from virtualDir where md5sum =",fileData.md5sum); 
    char bufSql[1000];
    int querySucess=querySqlFile(&sd,bufSql);
    printf("querySucess=%d,bufSql is %s\n",querySucess,bufSql);
    /* sprintf(sd.sql_command,"%s'%s','%s','f','%s')","insert into virtualDir (fileName,belongID,fileType,md5sum) values(" */
    /*         ,fileData.fileName,fileData.filePath,fileData.md5sum); */
    /* insertSql(&sd); */
    
    char precodebuf[10];
    int precodeTemp;
    char belongIDtemp[20];
    char delim[3]=" \n";
    if(-1==querySucess) {
        //第一次上传该文件
        sprintf(sd.sql_command,"%s%d,'%s','%s','f','%s')","insert into virtualDir (precode,fileName,belongID,fileType,md5sum) values("
                ,fileData.precode,fileData.fileName,fileData.filePath,fileData.md5sum);
        printf("sql command is %s\n",sd.sql_command);
        //printf("precodeTemp is %d,belongIDtemp is %s",precodeTemp,belongIDtemp);
        insertSql(&sd); 
    }
    if(0==querySucess){
        //不能在是同一个用户并且在同一个目录
        //服务器上有该文件，不再传输，只增加记录,
        strcpy(precodebuf,strtok(bufSql,delim));
        precodeTemp=atoi(precodebuf);
        strcpy(belongIDtemp,strtok(NULL,delim));
        //printf("precodeTemp is %d,belongIDtemp is %s",precodeTemp,belongIDtemp);
        if(0==strcmp(fileData.filePath,belongIDtemp)&&(fileData.precode==precodeTemp)){
            //是同一个用户并且在同一个目录，所以不插入记录
            close(socketFd);
            return 0;
        }
        bzero(&sd.sql_command,sizeof(sd.sql_command));
        printf("-------gets----belongID---is%s\n",fileData.filePath) ;
        sprintf(sd.sql_command,"%s%d,'%s','%s','f','%s')","insert into virtualDir (precode,fileName,belongID,fileType,md5sum) values("
                ,fileData.precode,fileData.fileName,fileData.filePath,fileData.md5sum);
        printf("sql command is %s\n",sd.sql_command);
        insertSql(&sd);
        //完成下载上传后关闭连接
        close(socketFd);
        return 0;
    }

    //计算该文件大小,并将该文件大小传给服务器
    int fd=open(fileData.md5sum,O_RDWR|O_CREAT,0666);
    ERROR_CHECK(fd,-1,"open");  
    struct stat fileInfo;
    fstat(fd,&fileInfo);
    printf("the filesize is %f\n",(float)fileInfo.st_size) ;
    bzero(&train,sizeof(Train_t));
    train.dataLen=sizeof(fileInfo.st_size);
    memcpy(train.buf,&fileInfo.st_size,train.dataLen);
    ret=send(socketFd,&train.dataLen,4,0);
    ERROR_CHECK(ret,-1,"send");
    ret=send(socketFd,train.buf,train.dataLen,0);
    ERROR_CHECK(ret,-1,"send");
    //接收文件大小
    off_t filesize,sliceSize,downloadSize;
    bzero(&train,sizeof(Train_t));
    ret=recvCycle(socketFd,&train.dataLen,4);
    printf("dataLen is %d\n",train.dataLen);
    ret=recvCycle(socketFd,train.buf,train.dataLen);
    printf("train.buf is %s\n",train.buf);
    memcpy(&filesize,train.buf,train.dataLen);
    printf("filesize is %ld\n",filesize);
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
    //close(socketFd);
    free(pvd);
    return 0;
}

