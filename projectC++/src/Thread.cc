 ///
 /// @file    Thread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-04 09:51:40
 ///
 

#include "Thread.h"

#include <stdio.h>
#include <errno.h>

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{
__thread const char * threadName="wd thread";

using ThreadCallback = std::function<void()>;

struct ThreadData
{
    string _name;
    ThreadCallback _cb;

    ThreadData(const string name,ThreadCallback cb)
    :_name(name) ,
    _cb(cb)
    {}

    void runInThread()
    {
        //任务执行之前，do something
        threadName = (_name == string ())?"wd thread" :_name.c_str();

        if(_cb){
            _cb();
        }

        //任务执行之后，do something
    }
};
/* Thread::Thread(ThreadCallback && cb) */
/* : _pthid(0) */
/* , _cb(std::move(cb)) */
/* , _isRunning(false) */
/* { */
/* 	cout << "Thread()" << endl; */
/* } */

void Thread::start()
{
    ThreadData *data =  new ThreadData(_name,_cb);
	
    if(pthread_create(&_pthid, NULL, threadFunc, data))
    {
        perror("pthread_create");
        return;
    }
	_isRunning = true;
}

void * Thread::threadFunc(void * arg)
{
	ThreadData * pdata = static_cast<ThreadData*>(arg);
	if(pdata)
		pdata->runInThread();

    delete  pdata;
	return nullptr;
}

void Thread::join()
{
    if(_isRunning){
		pthread_join(_pthid, NULL);
        _isRunning=false;
    }
}

Thread::~Thread()
{
	if(_isRunning) {
		pthread_detach(_pthid);	
        _isRunning=false;
	}
	cout << "~Thread()" << endl;
}

}//end of namespace wd
