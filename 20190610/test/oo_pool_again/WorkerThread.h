#pragma once

#include "Thread.h"
#include <iostream>
using namespace std;

namespace wd
{
class Threadpool;//防止头文件发生循环引用
class WorkThread
:public Thread
{
public:
    WorkThread(Threadpool & threadpool)
    :_threadpool(threadpool)
    {}
    ~WorkThread() {
        cout<<"~WorkThread()"<<endl;
    }

private:
    void run();
private:
    Threadpool &_threadpool;
};

}//end of wd
