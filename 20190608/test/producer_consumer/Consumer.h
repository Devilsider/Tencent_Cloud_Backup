#pragma once
#include "Thread.h"
#include "MutexLock.h"
#include "Condition.h"
#include "TaskQueue.h"

#include <unistd.h>
namespace wd
{

class Consumer
:public wd::Thread
{
public:
    Consumer()
    :_tasque(TaskQueue::getInstance()) 
    {}
    ~Consumer() 
    {
        cout<<"~Consumer()"<<endl;
    }
private:
    void run()override{
        while(1)
        {
            /* if(_tasque->empty()) { */
            /*     _tasque->getPNotEmpty()->wait(); */
            /* } */
            cout<<"I am Consumer "<<pthread_self()<<",I am going to consume"<<endl;
            int ret=_tasque->pop();
            cout<<"I am Consumer , get product "<<ret<<endl;
            sleep(1);
        }
    }
private:
    TaskQueue *_tasque;
};

}
