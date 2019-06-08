 ///
 /// @file    MutexLock.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-17 11:17:59
 ///
 
#ifndef __WD_MUTEXLOCK_H__
#define __WD_MUTEXLOCK_H__

#include <stdio.h>
#include <errno.h>
#include <pthread.h>


namespace wd
{

class MutexLock
{
public:
	MutexLock()
	: _isLocking(false)
	{
		if(pthread_mutex_init(&_mutex, NULL)) {
			perror("pthread_mutex_init");
		}
	}

	//c++11  表达禁止复制, 表达对象语义
	//C++天生支持复制 => 表达值语义(值传递)
	MutexLock(const MutexLock &) = delete;//被删除了
	MutexLock & operator=(const MutexLock &) = delete;

	~MutexLock()
	{
		if(pthread_mutex_destroy(&_mutex)) {
			perror("pthread_mutex_destroy");
		}
	}

	void lock()
	{
		if(pthread_mutex_lock(&_mutex)) {
			perror("pthread_mutex_lock");
		}
		_isLocking = true;
	}

	void unlock()
	{
		if(pthread_mutex_unlock(&_mutex)) {
			perror("pthread_mutex_unlock");
		}
		_isLocking = false;
	}

	bool isLocking() const {	return _isLocking;	}
	pthread_mutex_t * getMutexLockPtr() {	return &_mutex;	}

#if 0
private://禁止复制
	MutexLock(const MutexLock &);
	MutexLock & operator=(const MutexLock &);
#endif

private:
	pthread_mutex_t _mutex;
	bool _isLocking;
};


class MutexLockGuard 
{
public:
	MutexLockGuard(MutexLock & mutex)
	: _mutex(mutex)
	{
		_mutex.lock();
	}

	~MutexLockGuard()
	{
		_mutex.unlock();
	}

private:
	MutexLock & _mutex;
};

}//end of namespace wd
 

#endif
