#include<func.h>
int main(int argc,char* argv[]){
	ARGS_CHECK(argc,2);
	int fd=open(argv[1],O_RDWR|O_CREAT,0755);
	ERROR_CHECK(fd,-1,"open");
	ftruncate(fd,4096*1024*10);
	char *p;
	struct stat buf;
	fstat(fd,&buf);
	p=(char *)mmap(NULL,buf.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	ERROR_CHECK(p,(char *)-1,"mmap");
	memcpy(p,"world",strlen("world"));
	msync(p,4096,MS_ASYNC);
	munmap(p,buf.st_size);
	return 0;
}
