#include "function.h"
int makeChild(Process_Data *pChild,int childNum){
	//输入子进程的个数，还有子进程指针数组首地址
	int i;
	pid_t pid;
	int fds[2];//设置管道
	int ret;
	for(i=0;i<childNum;++i){
		ret=socketpair(AF_LOCAL,SOCK_STREAM,0,fds);//创建全双工管道
		ERROR_CHECK(ret,-1,"socketpair");
		pid=fork();
		if(0==pid){
			close(fds[1]);//关闭子进程管道1端
			childHandle(fds[0]);//对fds[0]进行读写操作	
		}
		close(fds[0]);
		pChild[i].pid=pid;
		pChild[i].fd=fds[1];
		pChild[i].busy=0;
	}
	return 0;
}
int childHandle(int fd){
	int newFd;
	while(1){
		recvFd(fd,&newFd);//接收父进程发来的new_fd，准备发送文件	
		tranFile(newFd);	//给客户端发送文件
		close(newFd);
		write(fd,&newFd,1);//通知父进程现在已空闲	
	}
}
