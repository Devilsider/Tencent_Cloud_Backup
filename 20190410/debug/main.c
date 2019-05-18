#include<stdio.h>
void main(){
#ifdef cjy
	printf("cjy is defined\n");
#else
	printf("cjy is not defined!\n");
#endif
	printf("main exit \n");
}

