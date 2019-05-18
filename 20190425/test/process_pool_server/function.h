#include <sys/epoll.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include <sys/socket.h>
#include<sys/msg.h>
#include <pthread.h>
#include <sys/time.h>
#include <signal.h>
#include<sys/sem.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<signal.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include<fcntl.h>
#include<errno.h>
#include<pwd.h>
#include<sys/mman.h>
#include<time.h>
#include<grp.h>
#include<sys/select.h>
#include<sys/wait.h>
#define ARGS_CHECK(argc,val){if(argc!=val)\
	{printf("error args\n");return -1;}}
#define ERROR_CHECK(ret,retval,funcName){if(ret==retval)\
	{printf("%d:",__LINE__);perror(funcName);return -1;}}
#define THREAD_ERROR_CHECK(ret,funcName){if(ret!=0)\
	{printf("%s:%s.\n",funcName,strerror(ret));return -1;}}
#define pTHREAD_ERROR_CHECK(ret,funcName){if(ret!=0)\
	{printf("%s:%s.\n",funcName,strerror(ret));return NULL;}}
//管理每一个子进程的数据结构
typedef struct {
	pid_t pid;//子进程的pid
	int fd;//子进程的管道对端
	short busy;//查看子进程忙碌状态，0为空闲，1为忙碌
}Process_Data;

int makeChild(Process_Data *,int);//创建子进程函数
int childHandle(int);//子进程处理函数
int tcpInit(int *,char *,char *);//封装建立tcp连接操作，使用tcpInit函数即可


