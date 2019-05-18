#include<func.h>
char* list_print_dir(char *path,char *filename){
	struct dirent *dirInfo;
	DIR *pDir;
	pDir=opendir(path);
 	ERROR_CHECK(pDir,NULL,"opendir");
	char newPath[512];		//存放新路径
	memset(newPath,'\0',sizeof(newPath));//初始化数组
	while((dirInfo=readdir(pDir))){
		if(strcmp(".",dirInfo->d_name)==0||strcmp("..",dirInfo->d_name)==0){
			continue;
		}
		if((strcmp(filename,dirInfo->d_name))==0){//寻找名为filename文件，判断文件名是否与目标文件相等
			printf("the path is %s\n",path);
			return path;
		}
		sprintf(newPath,"%s%s%s",path,"/",dirInfo->d_name);//读取的文件的新路径
		if(4==dirInfo->d_type){
			//如果是目录则继续递归遍历
				list_print_dir(newPath,filename);
		}
	}
	closedir(pDir);
 	return NULL;	//没有找到
}
int  main(int argc,char *argv[]){
	//第一个参数是路径，第二个参数是文件名
	ARGS_CHECK(argc,3);
	list_print_dir(argv[1],argv[2]);
	return 0;
}
