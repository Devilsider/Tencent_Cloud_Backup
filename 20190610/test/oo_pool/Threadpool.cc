#include "Threadpool.h"
#include "WorkThread.h"
#include <unistd.h>
#include <iostream>
using  namespace std;

namespace wd{

void Threadpool::start(){
    for(size_t  idx=0;idx!=_threadNum;++idx){
        unique_ptr<Thread> up(new WorkThread(*this));
        _threads.push_back(std::move(up));
    }

    for(auto &thread:_threads){
        thread->start();
    }
}

void Threadpool::addTask(Task * task){
    _taskque.push(task);
}

void Threadpool::stop(){
    if(!_isExit){
        
        while(!_taskque.empty()){
            ::sleep(1);
        }
        _isExit=true;
        for(auto &thread:_threads){
            pthread_cancel(thread->getPthid());
        }
        for(auto &thread:_threads){
            thread->join();
        }
    }
}

Task * Threadpool::getTask(){
    return _taskque.pop();
}

//WorkThread要执行的
void Threadpool::threadFunc(){
    while(!_isExit){
        Task * task  = getTask();
        if(task){
            task->process();
        }
    }
}

}
