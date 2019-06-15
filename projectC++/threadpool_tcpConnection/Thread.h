 ///
 /// @file    Thread.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-04 09:49:30
 ///
 
#ifndef __WD_THREAD_H__
#define __WD_THREAD_H__
#include "Noncopyable.h"

#include <pthread.h>
#include <functional>
#include <string>
using namespace std;
namespace wd
{

extern __thread const char * threadName;

class Thread
: Noncopyable
{
public:
	using ThreadCallback = std::function<void()>;

    Thread(ThreadCallback && cb,const string & name = string())
    :_pthid(0),
    _cb(move(cb)),
    _isRunning(false),
    _name(name)
    {}

	void start();
	void join();

	~Thread();

private:
	static void * threadFunc(void *);

private:
	pthread_t _pthid;
	ThreadCallback _cb;
	bool _isRunning; 
    string _name;
};

}//end of namespace wd

#endif
