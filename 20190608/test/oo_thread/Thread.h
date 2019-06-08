#pragma once
#include "Noncopyable.h"
#include <pthread.h>

namespace wd{
class Thread:Nocopyable
{
public:
    Thread() 
    :_pthId(0)
     ,_isRunning(false)
    {}

    virtual ~Thread();

    void start();
    void join();

private:
    virtual void run()=0;
    static void * threadFunc(void *);
private:
    pthread_t _pthId;
    bool _isRunning;
};

}
