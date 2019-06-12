#include "Threadpool.h"
#include <unistd.h>

#include <iostream>
using namespace std;

namespace wd
{
void Threadpool::start()
{
    for(size_t idx=0;idx!=_threadNum;++idx){
        unique_ptr<Thread> up(new Thread(
                        bind(&Threadpool::threadFunc,this)));
        _threads.push_back(std::move(up));
    }

    for(auto &thread: _threads){
        thread->start();
    }

}

void Threadpool::addTask(Task && task){
    _taskque.push(std::move(task));
}

void Threadpool::stop()
{
    if(!_isExit){
        //当队列中还有任务没有执行完毕的时候，等待
        while(!_taskque.empty()){
            sleep(1);
        }
        _isExit=true;
        _taskque.wakeup();
        for(auto &i:_threads){
            i->join();
        }

    }
}

Task Threadpool::getTask(){
    return _taskque.pop();
}

void Threadpool::threadFunc(){
    while(!_isExit){
        Task task=getTask();
        if(task){
            task();
        }
    }
}


}
