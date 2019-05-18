#include <func.h>
#define filesize 3221225472
int main()
{
    int fd=open("file",O_RDWR|O_CREAT,0666);
    ERROR_CHECK(fd,-1,"open");
    int ret=ftruncate(fd,filesize);
    ERROR_CHECK(ret,-1,"ftruncate")
    close(fd);
    return 0;
}

