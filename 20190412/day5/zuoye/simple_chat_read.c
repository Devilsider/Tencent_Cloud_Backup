#include<func.h>
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
	char buf[256];
	fd_set rdset;
	int ret;
	while(1){
		FD_ZERO(&rdset);//读写操作符初始化
		FD_SET(STDIN_FILENO,&rdset);//标准输入加入到操作符集合里面
		FD_SET(fdr,&rdset);//将fdr指向文件加入集合
   		ret=select(fdr+1,&rdset,NULL,NULL,NULL);
		if(ret>0){	
			if(FD_ISSET(fdr,&rdset)){
				//fdr指向管道文件可读，读取内容到buf输出
				printf("%s山本八十九:\n",asctime(timeinfo));
				memset(buf,'\0',sizeof(buf));
				ret=read(fdr,buf,sizeof(buf));//对于fdr只读,若返回值为0,写入字符数为0对方断开
				if(0==ret){
					//对方断开，此时rdset中可读集合数为0
					printf("SaYouLaLa!/n");
					break;
				}
				printf("%s\n",buf);
			}
			if(FD_ISSET(0,&rdset)){
				//标准输入可读时，读入标准输入内容
				memset(buf,'\0',sizeof(buf));
				ret=read(0,buf,sizeof(buf));//标准输入，将标准输入中的数据读到缓存中
				if(0==ret){
					printf("SaYouLaLa!\n");
					break;
				}
				write(fdw,buf,strlen(buf)-1);//对于fdw只写
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
