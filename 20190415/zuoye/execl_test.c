#include <func.h>
int main(int argc,char **argv){
	printf("execute add.h\n");
	execl("./add","add","3","4",NULL);
	return 0;
}
