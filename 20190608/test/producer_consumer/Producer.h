#pragma once
#include "Thread.h"
#include "MutexLock.h"
#include "Condition.h"
#include "TaskQueue.h"

#include <unistd.h>
namespace wd
{

class Producer
:public wd::Thread
{
public:
    Producer()
    :_tasque(TaskQueue::getInstance()) 
     ,_taskId(0)
    {
        _tasque->setQueSize(10);
    }
    ~Producer() 
    {
        cout<<"~Producer()"<<endl;
    }
private:
    void run()override{
        for(int idx=0;idx<10;++idx){
            /* _tasque->getPNotEmpty()->wait(); */
            cout<<"I am Producer "<<pthread_self()<<",I am going to produce"<<endl;
            _tasque->push(_taskId);
            ++_taskId;
            cout<<"I am Producer , mission clear"<<endl;
            sleep(1);
        }
    }
private:
    TaskQueue *_tasque;
    int _taskId;
};

}
