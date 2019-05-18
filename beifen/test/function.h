#include <mysql/mysql.h>
#include <sys/sendfile.h>
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
//多进程
//管理每一个子进程的数据结构
typedef struct {
	pid_t pid;//子进程的pid
	int fd;//子进程的管道对端
	short busy;//查看子进程忙碌状态，0为空闲，1为忙碌
}Process_Data;
//子进程采用该变长结构体发送数据
typedef struct{
	int dataLen;//控制数据，表示发送数据的长度，即客户端应该接收多少
	char buf[4096];//缓冲区，存放数据
}Train_t;
#define FILENAME "file"
int makeChild(Process_Data *,int);//创建子进程函数
int childHandle(int);//子进程处理函数
int tcpInit(int *,char *,char *);//封装建立tcp连接操作，使用tcpInit函数即可
int sendFd(int,int,int );//父进程向子进程发送new_fd，由子进程向客户端发送信息
int recvFd(int,int *,int *);//子进程接收父进程发送来的new_fd，向客户端发送信息
int tranFile(int);//子进程传送文件函数
int recvCycle(int,void*,int);//循环接收函数，解决发送大文件发送接收不同步的问题
int sendCycle(int,void*,int);
//多线程
typedef struct {
    int len;//数据长度
    int control_code;//数据控制码，表示为何种命令
    //1.cd
    //2.ls
    //3.puts
    //4.gets
    //5.remove
    //6.pwd
    //7.不响应
    //8.用户登录
    //9.用户注册
}Command_t;
typedef struct tag_node{//队列节点结构体
    int new_fd;
    struct tag_node *next;
}Node_t,*pNode_t;
typedef struct{
    pNode_t queHead,queTail;
    int queCapacity;//队列容量，即服务器允许最大客户端连接数
    int queSize;//队列实时大小
    pthread_mutex_t mutex;
}Que_t,*pQue_t;
void queInit(pQue_t,int);//初始化队列
void queInsert(pQue_t,pNode_t);//节点插入队列
int queGet(pQue_t,pNode_t*);//节点从队头出队

typedef struct{//线程管理结构体
    pthread_t *pthid;//存储线程ID的起始地址
    int threadNum;//创建线程的数目
 //   pthread_cond_t condA;//任务分类线程条件变量
    pthread_cond_t condL;//每个线程都要使用的条件变量下载上传的cond
    pthread_cond_t condS;//命令线程的cond
//    Que_t queAll;//任务队列，负责将命令分类，交给长命令和短命令队列 
    Que_t queLong;//生产者消费者操作的队列,只负责下载和上传的队列
    Que_t queShort;//只负责处理命令的队列
    short startFlag;//工厂启动标志
    short endFlag;//工厂退出标志
    pthread_mutex_t mutex;//工厂锁
    Command_t comm;//控制信息
}Factory_t,*pFactory_t;
void factoryInit(pFactory_t,int,int);//初始化线程
void factoryStart(pFactory_t);//给每一个线程分配任务
//数据库数据结构体
typedef struct {
    char sql_server[64];//服务器ip
    char sql_usr[64];//数据库登录用户名
    char sql_password[32];//数据库用户登录密码
    char sql_database[20];//数据库名称
    char sql_command[300];//执行的sql命令
}sqlData,*pSqlData;
typedef struct {
    //数据库中的用户数据结构体
    char name[20];//用户名
    char salt[64];//用户盐值
    char ciphertext[64];//加密后的密文
    int usr_new_fd;//对应的套接口
}usr,*pUsr;
int deleteSql(pSqlData psd);
int insertSql(pSqlData psd);
int querySql(pSqlData psd);
int updateSql(pSqlData psd);
