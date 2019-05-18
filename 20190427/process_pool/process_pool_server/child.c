#include "function.h"

int makeChild(Process_Data *pChild,int childNum)
{   
    int i;
    pid_t pid;
    int fds[2];
    int ret;
    for(i=0;i<childNum;++i){
        ret=socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
        ERROR_CHECK(ret,-1,"socketpair");
        pid=fork();
        if(0==pid){
            close(fds[1]);
            childHandle(fds[0]);
        }
        close(fds[0]);
        pChild[i].busy=0;
        pChild[i].fd=fds[1];
        pChild[i].pid=pid;
    }
    return 0;
}
int childHandle(int fds){
    int newFd;
    int exitFlag;
    while(1){
        recvFd(fds,&newFd,&exitFlag);//接收任务，收到fd
        if(exitFlag){
            tranFile(newFd);//通过newFd向客户端发送文件
            close(newFd);//关闭newFd
        }
        else{
            exit(0);
        }
        //通知父进程已完成下载任务，重置为空闲状态
        write(fds,&newFd,1);
    }
}
