#include<func.h>
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
		printf("read:%d,write:%d 山本八十九\n",fdr,fdw);
		char buf[256];
		time_t t;//打印时间
		struct tm *timeinfo;
		time(&t);
		timeinfo=localtime(&t);
		int ret;
		fd_set rdset;
		while(1){
			FD_ZERO(&rdset);
			FD_SET(STDIN_FILENO,&rdset);
			FD_SET(fdr,&rdset);//将fdr和标准输入加入到读操作集合里面
			ret=select(fdr+1,&rdset,NULL,NULL,NULL);
			if(ret>0){
				if(FD_ISSET(fdr,&rdset)){
					//fdr指向文件可读，读取内容输出	
					printf("%s龟田太郎:\n",asctime(timeinfo));
					memset(buf,'\0',sizeof(buf));
					ret=read(fdr,buf,sizeof(buf));//对fdr指向的文件进行读操作，返回值为0,返回字节数为0，对方断开
					if(0==ret){
						printf("SaYouLaLa!/n");
						break;
					}					
					printf("%s\n",buf);
				}
				if(FD_ISSET(0,&rdset)){
					//标准输入不为0，读入标准输入并且写入到fdr指向文件中
					memset(buf,'\0',sizeof(buf));
					ret=read(0,buf,sizeof(buf));//从标准输入中读入数据到缓存中
					if(0==ret){
						printf("SaYouLaLa!\n");
						break;
					}
					write(fdw,buf,strlen(buf)-1);//对fdw指向的文件进行写操作
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

