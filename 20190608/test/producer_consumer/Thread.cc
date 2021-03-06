#include "Thread.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>
using std::cout;
using std::endl;
namespace wd{

Thread::~Thread()
{
    if(_isRunning){
        pthread_detach(_pthId);
        _isRunning=false;
    }
    cout<<"~Thread()"<<endl;
}

void Thread::start(){
    if(pthread_create(&_pthId,NULL,threadFunc,this)){
        perror("pthread_create");
        return;
    }
    _isRunning=true;
}

void Thread::join(){
    if(_isRunning){
        pthread_join(_pthId,NULL);
        _isRunning=false;
    }
}

void * Thread::threadFunc(void *arg){
    Thread * pthread=static_cast<Thread*>(arg);
    if(pthread){
        pthread->run();
    }
    return NULL;
}

}

