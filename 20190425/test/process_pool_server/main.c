#include "function.h"
int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,4);
	int childNum=atoi(argv[3]);//设置创建子进程数目
	Process_Data *pChild=(Process_Data *)calloc(childNum,sizeof(Process_Data));//定义动态子进程指针数组
	makeChild(pChild,childNum);//创建childNum数目子进程
	
}

