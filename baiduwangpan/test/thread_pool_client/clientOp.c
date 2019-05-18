#include "function.h"

int pwdClient(int socketFd,pUsr_t pusr)
{
    //先给服务器发送用户信息
    int ret;
    Train_t train;
    Usr_t usr;
    strcpy(usr.name,pusr->name);
    strcpy(usr.salt,pusr->salt);
    strcpy(usr.ciphertext,pusr->ciphertext);
    usr.precode=pusr->precode;
    bzero(&train,sizeof(Train_t));
    train.dataLen=sizeof(usr);
    memcpy(train.buf,&usr,sizeof(usr));
    ret=send(socketFd,&train,4+train.dataLen,0);
    ERROR_CHECK(ret,-1,"send");

    char usrPath[100];
    bzero(&train,sizeof(Train_t));
    ret=recvCycle(socketFd,&train.dataLen,4);
    ret=recvCycle(socketFd,train.buf,train.dataLen);
    memcpy(usrPath,train.buf,train.dataLen);
    //printf("path is %s\n",usrPath);

    printf("%s\n",usrPath);




    return 0;
}

int cdClient(int socketFd,char path[],pUsr_t pusr,char newPath[]){
    //向服务器发送数据
    int ret;
    Train_t train;
    Usr_t usr;
    strcpy(usr.name,pusr->name);
    strcpy(usr.salt,pusr->salt);
    strcpy(usr.ciphertext,pusr->ciphertext);
    usr.precode=pusr->precode;
    bzero(&train,sizeof(Train_t));
    train.dataLen=sizeof(usr);
    memcpy(train.buf,&usr,train.dataLen);
    //发送用户
    ret=send(socketFd,&train,4+train.dataLen,0);
    ERROR_CHECK(ret,-1,"send");

    //发送路径
    bzero(&train,sizeof(Train_t));
    train.dataLen=strlen(path);
    memcpy(train.buf,path,train.dataLen);
    ret=send(socketFd,&train,4+train.dataLen,0);
    
    //接收来自服务器的路径
    bzero(&train,sizeof(Train_t));
    ret=recvCycle(socketFd,&train.dataLen,4);
    ERROR_CHECK(ret,-1,"recvCycle") ;
    ret=recvCycle(socketFd,train.buf,train.dataLen);
    ERROR_CHECK(ret,-1,"recvCycle") ;
//    printf("----------%s\n",train.buf);
    memcpy(newPath,train.buf,train.dataLen);
    //接收服务器发来的precode并记录
    bzero(&train,sizeof(Train_t));
    ret=recvCycle(socketFd,&train.dataLen,4);
    ERROR_CHECK(ret,-1,"recvCycle") ;
    ret=recvCycle(socketFd,train.buf,train.dataLen);
    int tot;
    memcpy(&tot,train.buf,train.dataLen);
    //printf("-------------%d\n",tot);
    pusr->precode=tot;
    return 0;
}
int lsClient(int socketFd,char path[],pUsr_t pusr){
    //向服务器发送数据
    int ret;
    Train_t train;
    Usr_t usr;
    strcpy(usr.name,pusr->name);
    strcpy(usr.salt,pusr->salt);
    strcpy(usr.ciphertext,pusr->ciphertext);
    usr.precode=pusr->precode;
    bzero(&train,sizeof(Train_t));
    train.dataLen=sizeof(usr);
    memcpy(train.buf,&usr,train.dataLen);
    //发送用户
    ret=send(socketFd,&train,4+train.dataLen,0);
    ERROR_CHECK(ret,-1,"send");

    //发送路径
    bzero(&train,sizeof(Train_t));
    train.dataLen=strlen(path);
    memcpy(train.buf,path,train.dataLen);
    ret=send(socketFd,&train,4+train.dataLen,0);
    
    //接收数据结果
    bzero(&train,sizeof(Train_t));
    ret=recvCycle(socketFd,&train.dataLen,4) ;
    ERROR_CHECK(ret,-1,"recvCycle");
    ret=recvCycle(socketFd,train.buf,train.dataLen);
    ERROR_CHECK(ret,-1,"recvCycle");
    //printf("-----train.buf---is---%s\n",train.buf);
   
    char lsBuf[256];
    //char fileBuf[100] ;
    memcpy(lsBuf,train.buf,train.dataLen);
    //printf("lsbuf----------%s\n",lsBuf);
    
    char delim[3]=" \n";
    char *p;
    p=strtok(lsBuf,delim);
    printf("%s ",p);
    p=strtok(NULL,delim);
    printf(" %s\n",p);
    while((p=strtok(NULL,delim))){
        printf("%s ",p);
        p=strtok(NULL,delim);
        printf(" %s\n",p);
    }
    return 0;
}

int removeClinet(int socketFd,char path[],pUsr_t pusr){
    //向服务器发送数据
    int ret;
    Train_t train;
    Usr_t usr;
    strcpy(usr.name,pusr->name);
    strcpy(usr.salt,pusr->salt);
    strcpy(usr.ciphertext,pusr->ciphertext);
    usr.precode=pusr->precode;
    bzero(&train,sizeof(Train_t));
    train.dataLen=sizeof(usr);
    memcpy(train.buf,&usr,train.dataLen);
    //发送用户
    ret=send(socketFd,&train,4+train.dataLen,0);
    ERROR_CHECK(ret,-1,"send");

    //发送路径
    bzero(&train,sizeof(Train_t));
    train.dataLen=strlen(path);
    memcpy(train.buf,path,train.dataLen);
    ret=send(socketFd,&train,4+train.dataLen,0);
    ERROR_CHECK(ret,-1,"send");
    
    return 0;
}


