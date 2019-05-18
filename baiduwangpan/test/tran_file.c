#include "function.h"
#define maxsize 104857600
#define maxMemorySize 2147483648
int tranFile(int newFd)
{
    int ret;
    Train_t train;
    bzero(&train,sizeof(train));
    fileInfo_t fileData;
    pVirtualDir_t pvd;
    pvd=(pVirtualDir_t)calloc(1,sizeof(virtualDir_t));
    char buffer[4096];
    //先接收客户端发过来的文件结构体信息
    bzero(&fileData,sizeof(fileInfo_t));
    ret=recvCycle(newFd,&train.dataLen,4);
    printf("train.dataLen is %d \n",train.dataLen) ;
    ERROR_CHECK(ret,-1,"recvCycle");
    ret=recvCycle(newFd,train.buf,train.dataLen);
    printf("train.buf is %s \n",train.buf) ;
    ERROR_CHECK(ret,-1,"recvCycle");
    memcpy(&fileData,train.buf,sizeof(fileInfo_t));
    printf("file.name is %s,file path is %s,file size is %ld\n",fileData.fileName,fileData.filePath,fileData.fileSize);
    
    //从数据库里面查找
    sqlData sd;
    bzero(&sd,sizeof(sqlData));
    strcpy(sd.sql_server,"localhost");
    strcpy(sd.sql_usr,"root");
    strcpy(sd.sql_password,"wow18771731658");
    strcpy(sd.sql_database,"baiduwangpan");
    
    bzero(sd.sql_command,sizeof(sd.sql_command));
    sprintf(sd.sql_command,"%s'%s',%d,'%s')","insert into usrOp (user,command,path) values("
              ,fileData.filePath,4,fileData.fileName);
    printf("---4--%s\n",sd.sql_command);
    insertSql(&sd);
    
    bzero(sd.sql_command,sizeof(sd.sql_command));
    sprintf(sd.sql_command,"%s'%s'and belongID ='%s'","select * from virtualDir where fileName=",
            fileData.fileName,fileData.filePath);
    int querySucess=querySqlFile(&sd,buffer);
    if(-1==querySucess){
        //数据库中没有该文件，无法传输，关闭
        free(pvd);
        return -1;
    }
   // printf("buffer is %s\n",buffer);
    char delim[3]=" \n";
    strtok(buffer,delim);
    for(int idx=0;idx<5;++idx){
        strcpy(fileData.md5sum,strtok(NULL,delim));
    }
    //printf("fileData.md5sum = %s\n",fileData.md5sum);
    


    /* printf("------------fileData.fileName is %s,fileData.filePath is %s,fileData.md5sum is %s\n" */
    /*        ,fileData.fileName,fileData.filePath,fileData.md5sum); */
    //再发文件信息结构体名字
    /* fileInfo_t filebuf; */ 
    /* bzero(&train,sizeof(Train_t)); */
    /* train.dataLen=sizeof(fileData); */
    /* memcpy(train.buf,&fileData,sizeof(fileInfo_t)); */
    /* memcpy(&filebuf,train.buf,sizeof(fileInfo_t)); */
    /* printf("filebuf.fileName is %s,filebuf.filePath is %s,filebuf.md5sum is %s",filebuf.fileName,filebuf.filePath,filebuf.md5sum); */
    /* printf("send train.buf=%s,ret=%d\n",train.buf,ret); */
    /* ret=send(newFd,&train.dataLen,4,0); */
    /* ERROR_CHECK(ret,-1,"send"); */
    /* printf("send train.dataLen=%d,ret=%d\n",train.dataLen,ret); */
    /* ret=s
     /* printf("send train.buf=%s,ret=%d\n",train.buf,ret); */
    /* ERROR_CHECK(ret,-1,"send"); */
    //存储为文件偏移量
    int dataLen;
    off_t offset;
    offset=fileData.fileSize;
    bzero(&train,sizeof(Train_t));
    /* recvCycle(newFd,&train.dataLen,4); */
    /* recvCycle(newFd,train.buf,train.dataLen) ; */
    /* memcpy(&offset,train.buf,train.dataLen); */
    //再发送文件大小
    int fd=open(fileData.md5sum,O_RDONLY);
    ERROR_CHECK(fd,-1,"open");
    struct stat buf;
    bzero(&buf,sizeof(buf));
    fstat(fd,&buf);
    train.dataLen=sizeof(buf.st_size);
    memcpy(train.buf,&buf.st_size,train.dataLen);
    ret=send(newFd,&train.dataLen,4,0);
    printf("send ret=%d,train.dataLen is %d\n",ret,train.dataLen);
    ERROR_CHECK(ret,-1,"send");
    ret=send(newFd,train.buf,train.dataLen,0);
    printf("send ret=%d,train.buf is %s\n",ret,train.buf);
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
          ret=sendCycle(newFd,&train,4);
          ERROR_CHECK(ret,-1,"send");
          goto end;
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
            ret=send(newFd,pStart,buf.st_size-upSize,0);
            ERROR_CHECK(ret,-1,"send");
            munmap(pStart,buf.st_size-upSize);
            upSize=upSize+ret;
            //发送文件结束标志
            bzero(&train,sizeof(train));
            ret=sendCycle(newFd,&train,4);
            ERROR_CHECK(ret,-1,"send");

        /*     
        ret=sendfile(newFd,fd,&upSize,buf.st_size-offset);
        upSize=upSize+ret;
        ERROR_CHECK(ret,-1,"sendfile");
         
    */ 
    }
    printf("upSize=%ld,buf.st_size=%ld\n",upSize,buf.st_size);
    bzero(&train,sizeof(Train_t));
    if(upSize==buf.st_size) {
        ret=send(newFd,&train,4,0);
        ERROR_CHECK(ret,-1,"send");
    }
end:
    close(fd);
    return 0;
}

