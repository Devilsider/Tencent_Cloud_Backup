#include "Timer.h"

#include <unistd.h>
#include <poll.h>
#include <sys/timerfd.h>

#include <iostream>
using namespace std;

namespace wd
{

void Timer::start()
{
    _isStarted=true;
    setTimer(_initalTime,_intervalTime);

    struct pollfd pfd;
    pfd.fd=_fd;
    pfd.events=POLLIN;

    while(_isStarted)
    {
        int nready = ::poll(&pfd,1,5000);
        if(nready==-1&&errno==EINTR)
        {
            continue;
        }
        else if(nready==-1)
        {
            perror("poll");
            return;
        }
        else if(nready==0)
        {
            cout<<">>poll timeout"<<endl;
        }
        else 
        {
            if(pfd.revents & POLLIN)
            {
                handleRead();//处理该事件
                if(_cb)
                {
                    _cb();
                }
            }
        }
    }
}

void Timer::stop()
{
    if(_isStarted)
    {
        setTimer(0,0);
        _isStarted=false;
    }
}

int Timer::createTimerfd()
{
    int fd=::timerfd_create(CLOCK_REALTIME,0);
    if(fd == -1){
        perror("timerfd_create");
    }
    return fd;
}

void Timer::setTimer(int initalTime,int intervalTime){
    struct itimerspec value;
    value.it_value.tv_sec=initalTime;
    value.it_value.tv_nsec=0;
    value.it_interval.tv_sec=intervalTime;
    value.it_interval.tv_nsec=0;
    
    int ret = ::timerfd_settime(_fd,0,&value,NULL);
    if(ret==-1)  {
        perror("timerfd_settime");
    }
}

void Timer::handleRead()
{
    uint64_t howmany;
    int ret=::read(_fd,&howmany,sizeof(howmany));
    if(ret != sizeof(howmany))
    {
        perror("read");
    }
}

}
