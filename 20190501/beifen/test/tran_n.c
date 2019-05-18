#include "function.h"
int recvCycle(int newFd,void *p,int len)
{
    int total=0;
    int ret;
    char *pStart=(char *)p;
    while(total<len){
        ret=recv(newFd,pStart+total,len-total,0);
        ERROR_CHECK(ret,-1,"recv");
        if(0==ret){
            return -1;
        }
        total=total+ret;
    }
    return 0;
}

