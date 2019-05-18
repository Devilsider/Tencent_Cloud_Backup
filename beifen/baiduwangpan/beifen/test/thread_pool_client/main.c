#include "function.h"

int main(int argc,char *argv[])
{
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
    char pwd[1000];
    char usr[1000];
    char bash[1000];
    char command[1000];//标准输入的命令
    char comm[10];//分离后的命令
    char path[1000];//分离后的路径
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
    switch(get){
        case 8:
            //发送用户登录信息
            //先发送控制码 
            bzero(&commd,sizeof(commd));
            commd.len=sizeof(Command_t);
            commd.control_code=8;
            ret=send(socketFd,&commd.len,4,0);
            ERROR_CHECK(ret,-1,"send");
            ret=send(socketFd,&commd,commd.len,0);
            ERROR_CHECK(ret,-1,"send");
            //发送用户信息
            bzero(&train,sizeof(Train_t));
            train.dataLen=sizeof(Usr_t)+4; 
            memcpy(train.buf,&usrInfo,sizeof(Usr_t));
            ret=send(socketFd,&train.dataLen,4,0);
            ERROR_CHECK(ret,-1,"send");
            ret=send(socketFd,&train,train.dataLen,0);
            ERROR_CHECK(ret,-1,"send");
            printf("usr.name=%s,usr.passwd=%s",usrInfo.name,usrInfo.ciphertext);
            //测试发送用户和密码是否正确
            //若ret=-1，则被服务器判断数据错误关闭对端
            ret=send(socketFd,0,0,0);
            if(-1==ret){
                printf("Wrong usr information,connection is denied\n");
                exit(0);
            }
            break;
        case 9:
            //发送用户注册信息;
            //发送控制码 
            bzero(&commd,sizeof(commd));  
            commd.len=sizeof(Command_t);
            commd.control_code=9;
            ret=send(socketFd,&commd.len,4,0);
            ERROR_CHECK(ret,-1,"send");
            ret=send(socketFd,&commd,commd.len,0);
            ERROR_CHECK(ret,-1,"send");
            //发送用户信息
            bzero(&train,sizeof(Train_t));
            train.dataLen=sizeof(Usr_t)+4;
            memcpy(train.buf,&usrInfo,sizeof(Usr_t));
            
            ret=send(socketFd,&train.dataLen,4,0);
            printf("ret=%d\n",ret); 
            ERROR_CHECK(ret,-1,"send");
            ret=send(socketFd,&train,train.dataLen,0);
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
            ret=recvCycle(socketFd,&commd,commd.len);
            if(-1==commd.control_code){
                printf("register failed o(╥﹏╥)o，please try again.\n");
                exit(0);
                //注册失败就关闭，先不实现循环注册
            }
            break;
        default:
            break;
    }
    while(1){ 
        //system("clear");
        sprintf(bash,"[%s %s~/]$ ",usr,pwd);
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
        commd.len=sizeof(Command_t);
        ret=send(socketFd,&commd.len,4,0);
        ERROR_CHECK(ret,-1,"send");
        printf("send commd.len = %d\n",ret);
        //commd.control_code=8; 
        ret=send(socketFd,&commd,commd.len,0);
        ERROR_CHECK(ret,-1,"send");
        printf("send commd = %d,commd.control_code=%d\n",ret,commd.control_code);

        
        switch(commd.control_code){
            case 1:
                    break;
            case 2:break;
            case 3:break;
            case 4:break;
            case 5:break;
            case 6:break;
            default:break;
        }
    }//通知服务器断开
    ret=send(socketFd,&dataLen,4,0);
    ERROR_CHECK(ret,-1,"send");
    close(socketFd);
    return 0;
}

