#include<func.h>
#define name0 "龟田太郎"
#define name1 "山本八十九"
#define pidFileB "./usrBConf"
//在通信之前先互相告知对方自己的进程id
typedef struct {
	char usrname[64];	
	pid_t pid;	
}UserInfo;

//进程A和A1之间通信用的结构体
typedef struct {
	long mytype;//0代表自己输入的数据，1为对端发送过来的数据
	char name[64];
	char buf[256];
}Data;
void sigFunc(int signum,siginfo_t *p1,void *p2)
{
	//进行资源清理，清理完成后exit退出
	//读取文件信息
	UserInfo temp;
	int fdt;
	fdt= open(pidFileB,O_RDWR);
	if(-1==fdt){
		perror("open");	
	}
	int ret= read(fdt,&temp,sizeof(UserInfo));	
	if(-1==fdt){
		perror("read");	
	}	
	close(fdt);	
	printf("pid name ：%s ,pidB:%d\n",temp.usrname,temp.pid);
	kill(temp.pid,SIGINT);
//	printf("Bye Bye :)\n");
	//释放信号量
	int semid=semget(1000,2,0600|IPC_CREAT);
	if(-1==semid){
		perror("semget");	
	}
	ret=semctl(semid,IPC_RMID,0);
	if(-1==ret){
		perror("semctl");	
	}
	//释放共享内存
	int shmid=shmget(1000,4096,0600|IPC_CREAT);
	if(-1==shmid){
		perror("shmget");	
	}
	ret =shmctl(1000,IPC_RMID,0);
	if(-1==ret){
		perror("shmctl");
	}
	kill(getpid(),SIGQUIT);
}

int main(int argc,char *argv[]){
	//读程序，读程序对fdr指向的文件只进行读操作
	//对于fdw指向的文件只进行写操作，实现管道通信
	ARGS_CHECK(argc,3);
	int fdr=open(argv[1],O_RDONLY);
	ERROR_CHECK(fdr,-1,"open");
	int fdw=open(argv[2],O_WRONLY);
	ERROR_CHECK(fdw,-1,"open");
	printf("--argv1:%d,argv2:%d 龟田太郎--\n",fdr,fdw);
	time_t t;
	struct tm *timeinfo;
	time(&t);
	timeinfo=localtime(&t);
	Data da;
	fd_set rdset;
	int ret;
	
	UserInfo me,othUsr;//othUsr为聊天对端信息，me是自己信息
	strcpy(me.usrname,"龟田太郎");
	me.pid=getpid();//自己的进程号
	//连接前互相传递进程号
	write(fdw,&me,sizeof(me));
	read(fdr,&othUsr,sizeof(othUsr));
	printf("othname:%s,othPid:%id.\n",othUsr.usrname,othUsr.pid);
	
	int fdp=open(pidFileB,O_RDWR);
	ERROR_CHECK(fdp,-1,"open");
	//将B端的信息写入文件中
	ret=write(fdp,&othUsr,sizeof(UserInfo));
	ERROR_CHECK(fdp,-1,"write");	
	close(fdp);	

	//初始化信号量，收到信号量时关闭两个进程
	struct sigaction act;
	act.sa_sigaction=sigFunc;	
	act.sa_flags=SA_SIGINFO;
	ret=sigaction(SIGINT,&act,NULL);
	ERROR_CHECK(ret,-1,"sigaction");

	//实现与A1的显示通信，初始化共享内存
	int shmid = shmget(1000,4096,0600|IPC_CREAT);
	ERROR_CHECK(shmid,-1,"shmget");
	Data *p=(Data *)shmat(shmid,NULL,0);
	
	//设置信号量,使用生产者消费者模型进行同步，
	//写一句，A1窗口输出一句,在对共享内存进行操作的时候加锁
	unsigned short arr[2]={1,0};
	int semid = semget(1000,2,0600|IPC_CREAT);
	ERROR_CHECK(semid,-1,"semget");
	ret = semctl(semid,0,SETALL,arr);
	ERROR_CHECK(ret,-1,"semctl");
	struct sembuf sopp,sopv;
	sopp.sem_num=0;
	sopp.sem_op=-1;
	sopp.sem_flg=SEM_UNDO;
	sopv.sem_num=1;
	sopv.sem_op=1;
	sopv.sem_flg=SEM_UNDO;

	while(1){
		FD_ZERO(&rdset);//读写操作符初始化
		FD_SET(STDIN_FILENO,&rdset);//标准输入加入到操作符集合里面
		FD_SET(fdr,&rdset);//将fdr指向文件加入集合
   		ret=select(fdr+1,&rdset,NULL,NULL,NULL);
		if(ret>0){	
			if(FD_ISSET(fdr,&rdset)){
				//fdr指向管道文件可读，读取内容到buf输出
				printf("%s山本八十九:\n",asctime(timeinfo));
				da.mytype=1;	
				strcpy(da.name,name1);	
				memset(da.buf,'\0',sizeof(da.buf));
				ret=read(fdr,da.buf,sizeof(da.buf));//对于fdr只读,若返回值为0,写入字符数为0对方断开
				ERROR_CHECK(ret,-1,"read");	
				if(0==ret){
					//对方断开，此时rdset中可读集合数为0
					printf("SaYouLaLa!/n");
					break;
				}

				//将数据写入到共享内存
				semop(semid,&sopp,1);
				memcpy(p,&da,sizeof(Data));	
				semop(semid,&sopv,1);	
				
				printf("%s\n",da.buf);
			}
			if(FD_ISSET(0,&rdset)){
				//标准输入可读时，读入标准输入内容
				da.mytype=0;
				strcpy(da.name,name0);
				memset(da.buf,'\0',sizeof(da.buf));
				ret=read(0,da.buf,sizeof(da.buf));//标准输入，将标准输入中的数据读到缓存中
				ERROR_CHECK(ret,-1,"read");	
				if(0==ret){
					printf("SaYouLaLa!\n");
					break;
				}
				write(fdw,da.buf,strlen(da.buf)-1);//对于fdw只写
		
				//数据写入到共享内存
				semop(semid,&sopp,1);
				memcpy(p,&da,sizeof(Data));
				semop(semid,&sopv,1);	
			}	
		}
		else{
		printf("time out!\n");
		}
	}
	printf("\n");
	close(fdr);
	close(fdw);
	return 0; 
}
