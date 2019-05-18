#include "function.h"
void *sigUp(void *p){
    pUsr_path_t pat=(pUsr_path_t)p;
    usr_path_t upat;
    bzero(&upat,sizeof(usr_path_t));
    memcpy(&upat,pat,sizeof(usr_path_t));
    //showMemory(pat->path,strlen(pat->path));
    //先向服务器发送控制码
    Command_t comd;
    int ret;
    bzero(&comd,sizeof(comd));
    comd.len=sizeof(int);
    comd.control_code=10;
    //bug1
    ret=send(pat->newFd,&comd.len,4,0);
   // printf("-send--comd------%d\n",ret);
    if(-1==ret){
        return NULL;
        close(pat->newFd);
        free(pat);
        pthread_exit(0);
    }
    //bug2 
    ret=send(pat->newFd,&comd.control_code,comd.len,0);
    //printf("-send--comd------%d\n",ret);
    if(-1==ret){
        return NULL;
        close(pat->newFd);
        free(pat);
        pthread_exit(0);
    }
    printf("---thread---- pat->path=%s,pat.newFd=%d\n",pat->path,pat->newFd);
    printf("---thread---- pat->usdname=%s,pat.usrprecode=%d\n",pat->usrInfo.name,pat->usrInfo.precode);
    clientTranFile(upat.newFd,upat.path,&upat.usrInfo);
    close(pat->newFd);
    free(pat);
    pthread_exit(0);
}

void *sigDown(void *p){
    pUsr_path_t pat=(pUsr_path_t)p;
    usr_path_t upat;
    bzero(&upat,sizeof(usr_path_t));
    memcpy(&upat,pat,sizeof(usr_path_t));
    //showMemory(pat->path,strlen(pat->path));
    //先向服务器发送控制码
    Command_t comd;
    int ret;
    bzero(&comd,sizeof(comd));
    comd.len=sizeof(int);
    comd.control_code=10;
    //bug1
    ret=send(pat->newFd,&comd.len,4,0);
   // printf("-send--comd------%d\n",ret);
    if(-1==ret){
        return NULL;
        close(pat->newFd);
        free(pat);
        pthread_exit(0);
    }
    //bug2 
    ret=send(pat->newFd,&comd.control_code,comd.len,0);
    //printf("-send--comd------%d\n",ret);
    if(-1==ret){
        return NULL;
        close(pat->newFd);
        free(pat);
        pthread_exit(0);
    }
    printf("---thread---- pat->path=%s,pat.newFd=%d\n",pat->path,pat->newFd);
    printf("---thread---- pat->usdname=%s,pat.usrprecode=%d\n",pat->usrInfo.name,pat->usrInfo.precode);
    tranFile(upat.newFd,upat.path,&upat.usrInfo);
    close(pat->newFd);
    free(pat);
    pthread_exit(0);
}
int main(int argc,char *argv[])
{
RESTART:
    //argv[1]是ip地址，argv[2]是port是端口号
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
    printf("I am clever client(*>_<*)!,connect success.\n");
    Train_t train;
    int dataLen;
    char buf[4096];
    char pwd[100];
    char usr[100];
    char bash[100];
    char command[100];//标准输入的命令
    char comm[10];//分离后的命令
    char path[100];//分离后的路径
    char newPath[100];
    //登录验证或者是注册 
    Usr_t usrInfo;

    Command_t commd;
    bzero(&train,sizeof(Train_t)) ;
    bzero(pwd,sizeof(pwd));
    bzero(usr,sizeof(usr));
    bzero(bash,sizeof(bash));
    strcpy(usr,"username@VM-0-15-ubuntu");
    
    //用户必须先登录或者注册 
    int get=usrUi(&usrInfo);
    printf("usrInfo.name =%s,usrInfo.passwd=%s\n",usrInfo.name,usrInfo.ciphertext);
   // usrInfo.precode=42;//测试用
    switch(get){
        case 8:
            {
                //发送用户登录信息
                //先发送控制码 
                bzero(&commd,sizeof(commd));
                commd.len=sizeof(int);
                commd.control_code=8;
                //bug1
                ret=send(socketFd,&commd.len,4,0);
                printf("-send--commd------%d\n",ret);
                ERROR_CHECK(ret,-1,"send");
                //bug2 
                ret=send(socketFd,&commd.control_code,commd.len,0);
                printf("-send--commd------%d\n",ret);
                ERROR_CHECK(ret,-1,"send");
                
                /* //先接收salt值 */
                /* char salt[64]; */
                /* bzero(&train,sizeof(train)); */
                /* ret=recvCycle(socketFd,&train.dataLen,4); */
                /* ERROR_CHECK(ret,-1,"recvCycle"); */
                /* ret=recvCycle(socketFd,train.buf,train.dataLen); */
                /* ERROR_CHECK(ret,-1,"recvCycle"); */
                /* memcpy(salt,train.buf,train.dataLen); */
                /* printf("------salt---is %s\n",salt); */
                
                //发送用户信息
                bzero(&train,sizeof(Train_t));
                train.dataLen=sizeof(Usr_t); 
                memcpy(train.buf,&usrInfo,sizeof(Usr_t));
                ret=send(socketFd,&train.dataLen,4,0);
                ERROR_CHECK(ret,-1,"send");
                ret=send(socketFd,train.buf,train.dataLen,0);
                ERROR_CHECK(ret,-1,"send");
                printf("usr.name=%s,usr.salt=%s,usr.passwd=%s\n",usrInfo.name,usrInfo.salt,usrInfo.ciphertext);
                //测试发送用户和密码是否正确
                
                
                //接收salt值
                char salt[64];
                bzero(&train,sizeof(train));
                ret=recvCycle(socketFd,&train.dataLen,4);
                ERROR_CHECK(ret,-1,"recvCycle");
                ret=recvCycle(socketFd,train.buf,train.dataLen);
                ERROR_CHECK(ret,-1,"recvCycle");
                memcpy(salt,train.buf,train.dataLen);
                printf("------salt---is %s\n",salt);
                
                char passwd[64];
                strcpy(passwd,usrInfo.ciphertext);
                bzero(&usrInfo.ciphertext,sizeof(usrInfo.ciphertext));
                strcpy(usrInfo.ciphertext,crypt(passwd,salt));
                
                //加密后再发送用户信息
                bzero(&train,sizeof(Train_t));
                train.dataLen=sizeof(Usr_t); 
                memcpy(train.buf,&usrInfo,sizeof(Usr_t));
                ret=send(socketFd,&train.dataLen,4,0);
                ERROR_CHECK(ret,-1,"send");
                ret=send(socketFd,train.buf,train.dataLen,0);
                ERROR_CHECK(ret,-1,"send");
                printf("usr.name=%s,usr.salt=%s,usr.passwd=%s\n",usrInfo.name,usrInfo.salt,usrInfo.ciphertext);
                
                
                //若ret=-1，则被服务器判断数据错误关闭对端
                bzero(&commd,sizeof(Command_t));
                ret=recvCycle(socketFd,&commd.len,4);
                ERROR_CHECK(ret,-1,"recv");
                ret=recvCycle(socketFd,&commd.control_code,commd.len);
                if(-1==commd.control_code){
                    printf("login failed o(╥﹏╥)o，please try again.\n");
                    exit(0);
                    //登录失败就关闭，先不实现循环登录
                }
                bzero(newPath,sizeof(newPath));
                /* ret=send(socketFd,0,0,0); */
                /* if(-1==ret){ */
                /*     printf("Wrong usr information,connection is denied\n"); */
                /*     exit(0); */
                /* } */
                break;
            }
        case 9:
            {
                //发送用户注册信息;
                //发送控制码 
                bzero(&commd,sizeof(commd));  
                commd.len=sizeof(int);
                commd.control_code=9;
                ret=send(socketFd,&commd.len,4,0);
                ERROR_CHECK(ret,-1,"send");
                ret=send(socketFd,&commd.control_code,commd.len,0);
                ERROR_CHECK(ret,-1,"send");
                
                char salt[64];
                bzero(&train,sizeof(train));
                ret=recvCycle(socketFd,&train.dataLen,4);
                ERROR_CHECK(ret,-1,"recvCycle");
                ret=recvCycle(socketFd,train.buf,train.dataLen);
                ERROR_CHECK(ret,-1,"recvCycle");
                memcpy(salt,train.buf,train.dataLen);
                printf("----salt-----is---%s\n",train.buf);
                char passwd[64];
                strcpy(passwd,usrInfo.ciphertext);
                bzero(&usrInfo.ciphertext,sizeof(usrInfo.ciphertext));
                strcpy(usrInfo.ciphertext,crypt(passwd,salt));
                printf("------ciphertext---is---%s\n",usrInfo.ciphertext);
                
                //对用户密码加密发过去
                //发送用户信息
                bzero(&train,sizeof(Train_t));
                train.dataLen=sizeof(Usr_t);
                memcpy(train.buf,&usrInfo,sizeof(Usr_t));
                
                ret=send(socketFd,&train.dataLen,4,0);
                printf("ret=%d\n",ret); 
                ERROR_CHECK(ret,-1,"send");
                ret=send(socketFd,train.buf,train.dataLen,0);
                printf("ret=%d\n",ret); 
                ERROR_CHECK(ret,-1,"send");
                printf("usr.name=%s,usr.passwd=%s",usrInfo.name,usrInfo.ciphertext);
                //测试发送用户和密码是否正确
                //若ret=-1，则被服务器判断数据错误关闭对端
                ret=send(socketFd,0,0,0);
                if(-1==ret){
                    printf("Wrong usr information,connection is denied\n");
                    exit(0);
                }
                bzero(&commd,sizeof(Command_t));
                ret=recvCycle(socketFd,&commd.len,4);
                ERROR_CHECK(ret,-1,"recv");
                ret=recvCycle(socketFd,&commd.control_code,commd.len);
                if(-1==commd.control_code){
                    printf("register failed o(╥﹏╥)o，please try again.\n");
                    exit(0);
                    //注册失败就关闭，先不实现循环注册
                }
                //注册完成必须重新登录
                goto RESTART; 
                break;
            }
        default:
            break;
    }
    while(1){ 
        //system("clear");
        bzero(bash,sizeof(bash));
        sprintf(bash,"[%s %s~%s]$ ",usr,pwd,newPath);
        printf("\r%s",bash);
        bzero(command,sizeof(command));
        bzero(comm,sizeof(comm));
        bzero(path,sizeof(path));
        bzero(&commd,sizeof(commd));
        fgets(command,sizeof(command),stdin);
        commandRead(command,comm,path);
        printf("I am client,command is %s,path is %s \n",comm,path);
        ret=commandCheck(comm,path);
        commd.control_code=ret; 
        while(-1==ret) {
            fflush(stdin);
            printf("\n");
            printf("command not found!please enter again:)\n");
            printf("\r%s",bash);
            bzero(command,sizeof(command));
            bzero(comm,sizeof(comm));
            bzero(path,sizeof(path));
            bzero(&commd,sizeof(commd));
            fgets(command,sizeof(command),stdin);
            commandRead(command,comm,path);
            ret=commandCheck(comm,path);
            commd.control_code=ret; 
            printf("I am client,command is %s,path is %s \n",comm,path);
        }
        //先发送命令
        printf("control_code is %d\n",commd.control_code);
        commd.len=sizeof(int);
        ret=send(socketFd,&commd.len,4,0);
        ERROR_CHECK(ret,-1,"send");
        printf("send commd.len = %d\n",ret);
        //commd.control_code=8; 
        ret=send(socketFd,&commd.control_code,commd.len,0);
        ERROR_CHECK(ret,-1,"send");
        printf("send commd = %d,commd.control_code=%d\n",ret,commd.control_code);

        
        switch(commd.control_code){
            case 1:
                {
                    printf("\n");
                    bzero(newPath,sizeof(newPath));
                    cdClient(socketFd,path,&usrInfo,newPath);
                    printf("---main--precode---%d\n",usrInfo.precode);
                    printf("---main--newPath---%s\n",newPath);
                    break;
                }
            case 2:{
                       lsClient(socketFd,path,&usrInfo);
                       break;
                   }
            case 3:
                   {   //四期需修改,改为多线程，让子线程上传文件
                       //创建子线程,传入path和usrInfo
                       pUsr_path_t pUpat;
                       pUpat=(pUsr_path_t )calloc(1,sizeof(usr_path_t));
                       pthread_t * ppth;
                       ppth=(pthread_t *)calloc(1,sizeof(pthread_t)); 
                       strcpy(pUpat->path,path);
                       printf("-------pUpat.path is %s\n",pUpat->path);
                       strcpy(pUpat->usrInfo.name,usrInfo.name);
                       strcpy(pUpat->usrInfo.ciphertext,usrInfo.ciphertext);
                       strcpy(pUpat->usrInfo.salt,usrInfo.salt);
                       pUpat->usrInfo.precode=usrInfo.precode;
                       int newSocketFd;
                       newSocketFd=socket(AF_INET,SOCK_STREAM,0);
                       ret=connect(newSocketFd,(struct sockaddr*)&ser,sizeof(struct sockaddr_in));
                       ERROR_CHECK(ret,-1,"connect");
                       pUpat->newFd=newSocketFd;
                       //printf("fffff-------pUpat.path is %s\n",pUpat->path);
                       pthread_create(ppth,NULL,sigUp,pUpat);
                       //printf("bbbb-------pUpat.path is %s\n",pUpat->path);
                       //tranFile(socketFd,path,&usrInfo);
                       break;
                   }
            case 4:
                   {
                       pUsr_path_t pUpat;
                       pUpat=(pUsr_path_t )calloc(1,sizeof(usr_path_t));
                       pthread_t * ppth;
                       ppth=(pthread_t *)calloc(1,sizeof(pthread_t)); 
                       strcpy(pUpat->path,path);
                       printf("-------pUpat.path is %s\n",pUpat->path);
                       strcpy(pUpat->usrInfo.name,usrInfo.name);
                       strcpy(pUpat->usrInfo.ciphertext,usrInfo.ciphertext);
                       strcpy(pUpat->usrInfo.salt,usrInfo.salt);
                       pUpat->usrInfo.precode=usrInfo.precode;
                       int newSocketFd;
                       newSocketFd=socket(AF_INET,SOCK_STREAM,0);
                       ret=connect(newSocketFd,(struct sockaddr*)&ser,sizeof(struct sockaddr_in));
                       ERROR_CHECK(ret,-1,"connect");
                       pUpat->newFd=newSocketFd;
                      //  printf("fffff-------pUpat.path is %s\n",pUpat->path);
                       pthread_create(ppth,NULL,sigDown,pUpat);
                       // printf("bbbb-------pUpat.path is %s\n",pUpat->path);
                       //clientTranFile(socketFd,path,&usrInfo);
                       break;
                   }
            case 5:
                   {
                       removeClinet(socketFd,path,&usrInfo);
                       break;
                   }
            case 6:{
                       pwdClient(socketFd,&usrInfo);
                       break;
                   }
            default:break;
        }
    }//通知服务器断开
    bzero(&dataLen,sizeof(dataLen));
    ret=send(socketFd,&dataLen,4,0);
    ERROR_CHECK(ret,-1,"send");
    close(socketFd);
    return 0;
}

