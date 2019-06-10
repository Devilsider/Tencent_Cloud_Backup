#include "WorkerThread.h"
#include "Threadpool.h"
namespace  wd{

void WorkThread::run(){
    _threadpool.threadFunc();
}
}
