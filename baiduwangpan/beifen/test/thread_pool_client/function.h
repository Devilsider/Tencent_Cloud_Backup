#define _GNU_SOURCE
#include <crypt.h>
#include <shadow.h>
#include <termios.h>
#include <openssl/md5.h>
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
#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)
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
//子进程采用该变长结构体发送数据
typedef struct{
	int dataLen;//控制数据，表示发送数据的长度，即客户端应该接收多少
	char buf[1000];//缓冲区，存放数据
}Train_t;
typedef struct {
    int len;//发送数据长度
    int control_code;//命令控制码
}Command_t;
#define FILENAME "file"
int makeChild(Process_Data *,int);//创建子进程函数
int childHandle(int);//子进程处理函数
int tcpInit(int *,char *,char *);//封装建立tcp连接操作，使用tcpInit函数即可
int sendFd(int,int );//父进程向子进程发送new_fd，由子进程向客户端发送信息
int recvFd(int,int *);//子进程接收父进程发送来的new_fd，向客户端发送信息
int recvCycle(int,void*,int);//循环接收函数，解决发送大文件发送接收不同步的问题
//百度网盘数据结构体
typedef struct {
    //数据库中的用户结构体
    //客户端不包括newfd 
    char name[20];
    char salt[64];
    char ciphertext[256];
    int precode;
}Usr_t,*pUsr_t;
typedef struct{
    //数据库中文件信息结构体
    char fileName[64];
    char filePath[128];
    char md5sum[256];
    off_t fileSize;
    int precode;
}fileInfo_t,*pFileInfo_t;
typedef struct{
    //数据库中虚拟文件目录结构体
    int percode;
    char vir_fileName[64];
    char vir_belongID[20];
    char vir_fileType[10];
    char vir_md5sum[256];
    long int vir_filesize;
}virtualDir_t,*pVirtualDir_t;
void commandRead(char *,char *,char *);//从标准输入中读取输入的命令，将其拆分，命令存到第二个字符串数组，路径存到第三个字符串数组
int commandCheck(char *,char *);
int usrUi(pUsr_t pusr);
void usrLog(pUsr_t pusr);
//函数set_disp_mode用于控制是否开启输入回显功能
//如果option为0，则关闭回显，为1则打开回显
int set_disp_mode(int fd,int option);
int tranFile(int newFd,char *,pUsr_t);
int Compute_file_md5(const char *file_path, char *value);
int clientTranFile(int socketFd,char path[],pUsr_t pusr);
int pwdClient(int,pUsr_t);
int cdClient(int,char *,pUsr_t,char *);
int lsClient(int socketFd,char path[],pUsr_t pusr);
int removeClinet(int socketFd,char path[],pUsr_t pusr);
