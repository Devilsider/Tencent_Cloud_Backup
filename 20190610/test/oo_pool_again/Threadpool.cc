#include "Threadpool.h"
#include "WorkerThread.h"

#include <unistd.h>
#include <iostream>
using namespace std;

namespace wd
{
void Threadpool::start()
{
    for(size_t idx=0;idx!=_threadNum;++idx){
        unique_ptr<Thread> up(new WorkThread(*this));
        _threads.push_back(move(up));
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
        //当队列中还有任务没有执行完的时候，等待
        while(!_taskque.empty()){
            sleep(1);
        }

        for(auto &thread:_threads){
            pthread_cancel(thread->getPthid());
        }
        for(auto &thread:_threads){
            thread->join();
        }
    }
}

Task* Threadpool::getTask(){
    return _taskque.pop();
}
void Threadpool::threadFunc(){
    while(!_isExit){
        Task *task=getTask();
        if(task){
            task->process();
        }
    }
}
}
