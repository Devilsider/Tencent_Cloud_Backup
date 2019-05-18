#include<func.h>
#define type0 1  
#define type1 2 
#define name0 "山本八十九" //自己的名字
#define name1 "龟田太郎"   //对端的名字
#define pidFileA "./usrAConf"
//通信之前先告诉对方自己的pid
//运用消息队列和B1通信
typedef struct {
	char usrname[64];
	pid_t pid;
}UserInfo;

/*msgsnd invalid argument 有错误，暂时先不用
typedef struct{
	//发送的数据
	long mytype;//0代表自己发送的数据，1为对端A发送过来的数据
	char name[64];
	char buf[256];
}Data;
*/
typedef struct msgbuf{
	//消息队列结构体
	long mytype;
	char mtext[64];	
}MSG;

void sigFunc(int signum,siginfo_t *p1,void *p2){
	//资源清理，消息队列
	//读取B端pid	
	UserInfo temp;	
	int fdt;
	fdt=open(pidFileA,O_RDWR);
	if(-1==fdt){
		perror("open");	
	}	
	int ret=read(fdt,&temp,sizeof(UserInfo));
	if(-1==fdt){
		perror("read");
	}
	close(fdt);	
	kill(temp.pid,SIGINT);
//	printf("pid A:%d\n",temp.pid);	

	printf("Bye Bye :)\n");
	int msgID=msgget(1000,IPC_CREAT|0600);
	if(-1==msgID){
		perror("msgID");	
	}
	ret=msgctl(msgID,IPC_RMID,NULL);
	if(-1==ret){
		perror("msgctl");
	}
	kill(getpid(),SIGQUIT);
}

int main(int argc,char *argv[]){
		//写程序，对于fdr文件描述符指向的文件只进行读操作，
		//对于fdw指向的文件只进行写操作，实现管道通信
		//即对argv[1]进行写，对argv[2]进行读
		//fdw->参数1，fdr->参数2
		ARGS_CHECK(argc,3);
		int fdw=open(argv[1],O_WRONLY);
		ERROR_CHECK(fdw,-1,"open");
		int fdr=open(argv[2],O_RDONLY);
		ERROR_CHECK(fdr,-1,"open");
		printf("--argv[0]:%d,argv[1]:%d 山本八十九--\n",fdr,fdw);
		time_t t;//打印时间
		struct tm *timeinfo;
		time(&t);
		timeinfo=localtime(&t);
		int ret;
		fd_set rdset;
	
		UserInfo me,othUsr;//othUsr为聊天对端信息，me是自己信息
		strcpy(me.usrname,"山本八十九");
		me.pid=getpid();//自己的进程号
		//连接前互相传递进程号
		write(fdw,&me,sizeof(me));
		read(fdr,&othUsr,sizeof(othUsr));
		printf("othname:%s,othPid:%id.\n",othUsr.usrname,othUsr.pid);
	
		int fdp=open(pidFileA,O_RDWR);
		ERROR_CHECK(fdp,-1,"open");	
		//将A端的信息写入到文件中，在sigFunc中读取
		ret=write(fdp,&othUsr,sizeof(UserInfo));
		ERROR_CHECK(ret,-1,"write");	
		close(fdp);	
		
		
		//设置信号处理函数，捕捉信号SIGINT
		struct sigaction act;
		act.sa_sigaction=sigFunc;
		act.sa_flags=SA_SIGINFO;
		ret=sigaction(SIGINT,&act,NULL);
		ERROR_CHECK(-1,ret,"sigaction");
	
		//初始化消息队列		
		int msgID;
		msgID=msgget(1000,0600|IPC_CREAT);
		ERROR_CHECK(msgID,-1,"msgget");
		MSG sndmsg;

		while(1){
			FD_ZERO(&rdset);
			FD_SET(STDIN_FILENO,&rdset);
			FD_SET(fdr,&rdset);//将fdr和标准输入加入到读操作集合里面
			ret=select(fdr+1,&rdset,NULL,NULL,NULL);
			if(ret>0){	
				if(FD_ISSET(fdr,&rdset)){
					//fdr指向文件可读，读取内容输出	
					sndmsg.mytype=type1;//表示从对端B读过来的数据
					
					memset(sndmsg.mtext,'\0',sizeof(sndmsg.mtext));
					ret=read(fdr,sndmsg.mtext,sizeof(sndmsg.mtext));//对fdr指向的文件进行读操作，返回值为0,返回字节数为0，对方断开
						
					if(0==ret){
						printf("SaYouLaLa!/n");
						break;
					}
					//使用消息队列给b1进程发送消息
					ret=msgsnd(msgID,&sndmsg,strlen(sndmsg.mtext),0);	
					ERROR_CHECK(ret,-1,"msgsnd");
					
				}
				if(FD_ISSET(0,&rdset)){
					//标准输入不为0，读入标准输入并且写入到fdr指向文件中
					sndmsg.mytype=type0;
					memset(sndmsg.mtext,'\0',sizeof(sndmsg.mtext));
					ret=read(0,sndmsg.mtext,sizeof(sndmsg.mtext));//从标准输入中读入数据到缓存中
					if(0==ret){
						printf("SaYouLaLa!\n");
						break;
					}
					write(fdw,sndmsg.mtext,strlen(sndmsg.mtext)-1);//对fdw指向的文件进行写操作
					ret=msgsnd(msgID,&sndmsg,strlen(sndmsg.mtext),0);
					ERROR_CHECK(ret,-1,"msgsnd");
				}
			}
			else{
				printf("time out!\n");
		
			}
		}
		close(fdw);
		close(fdr);
		return 0;
 }

