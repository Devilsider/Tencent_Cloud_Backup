#include<func.h>
int ll(char *path){
	DIR *pDir;
	pDir=opendir(path);
	struct stat buf;
	if(pDir==NULL){
		return -1;
	}
	struct dirent *dirInfo;
	while((dirInfo=readdir(pDir))){
		stat(dirInfo->d_name,&buf);
		char date[128];//将修改时间缓存过来
		memset(date,'\0',sizeof(date));
		strcpy(date,ctime(&buf.st_mtime));
		date[strlen(date)-1]='\0';//将最后一个\n去掉
		if(4==dirInfo->d_type){//是目录输出加斜杠
			printf("%-x %-ld %-s %-s %-10ld %-s %-s/\n",buf.st_mode,buf.st_nlink,getpwuid(buf.st_uid)->pw_name,getgrgid(buf.st_gid)->gr_name,buf.st_size,date,dirInfo->d_name);
		}
		else{
			printf("%-x %-ld %-s %-s %-10ld %-s %-s\n",buf.st_mode,buf.st_nlink,getpwuid(buf.st_uid)->pw_name,getgrgid(buf.st_gid)->gr_name,buf.st_size,date,dirInfo->d_name);	
		}
	}
	closedir(pDir);
	return 0;
}
int main(int argc,char *argv[]){
	ARGS_CHECK(argc,2);
	ll(argv[1]);
	return 0;
}
