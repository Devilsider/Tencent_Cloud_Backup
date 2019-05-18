#include<func.h>
#define student_num 10
typedef struct _s{
	int ID;
	char name[20];
	int score;
}Student;

int main(int argc,char* argv[]){
	Student s[10];
	ARGS_CHECK(argc,2);
	//初始化结构体数组	

	int fd=open(argv[1],O_RDWR|O_CREAT,0755);
	ERROR_CHECK(fd,-1,"open");
	for(int idx=0;idx<student_num;++idx)
	{
		s[idx].ID=idx;
		strcpy(s[idx].name,"zsk");
		s[idx].score=idx+10;
	}
	int ret=write(fd,s,sizeof(s));
	
	memset(s,'0',sizeof(s));
	for(int idx=0;idx<10;++idx){
		printf("ID:%d,name:%s,score:%d\n",s[idx].ID,s[idx].name,s[idx].score);
	}
	//重置指针
	lseek(fd,-sizeof(s),SEEK_CUR);
	while((ret=read(fd,s,sizeof(s)))>0){
		ERROR_CHECK(ret,-1,"read");
	}
	for(int idx=0;idx<10;++idx){
		printf("ID:%d,name:%s,score:%d\n",s[idx].ID,s[idx].name,s[idx].score);
	}
	close(fd);
	return 0;	
}
