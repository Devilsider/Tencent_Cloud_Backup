#include<func.h>
#define FILENAME1 "./aaa.txt"
#define FILENAME2 "./bbb.txt"
int main(){
	char buf[512]={0};
	int fo1=open(FILENAME1,O_RDONLY);
	int fo2=creat(FILENAME2,0755);
	if((-1==fo1)||(-1==fo2)){
		perror("open failed!");
		exit(-1);
	}
	int fr= 0;
	while((fr=read(fo1,buf,sizeof(buf)))>0){
		//如果读取成功，返回的是长度，否则返回-1
		int fw=write(fo2,buf,fr);
		if(-1==fw){
			perror("write failed!");
			exit(-1);
		}
	}
	close(fo1);
	close(fo2);
}

