#pragma once
#include "MutexLock.h"
#include "Condition.h"

#include <pthread.h>
#include <queue>
#include <iostream>

using namespace std;

namespace wd{

class TaskQueue
{
public:
    static TaskQueue * getInstance(){
        pthread_once(&_once,init);
        return _pInstance;
    }
    static void init(){
        _pInstance=new TaskQueue();
    }
    void destroy(){
        if(_pInstance){
            delete _pInstance;
        }
        cout<<"destroy()"<<endl;
    }
    void setQueSize(int capacity){
        _mutex.lock();
        _queSize=capacity;
        _mutex.unlock();
    }
    int getQueSize(){
        return _queSize;
    }
    void push(int taskid){
        _mutex.lock();
        if(full()){
            cout<<" que is full "<<endl;
        _mutex.unlock();
            return;
        }
        _que.push(taskid);
        _notEmpty.notify();
        _mutex.unlock();
    }
    int pop(){
        _mutex.lock();
        if(empty()){
            cout<<" que is empty"<<endl;
        _mutex.unlock();
            return (int)NULL;
        }
        int temp = _que.front();
        _que.pop();
        _notFull.notifyAll();
        _mutex.unlock();
        return temp;
    }
    bool full(){
        if(_queSize==_que.size()){
            return true;
        }
        return false;
    }
    bool empty(){
        if(0==_que.size()){
            return true;
        }
        return false;
    }
    Condition *getPNotFull(){
        return &_notFull;
    }
    Condition* getPNotEmpty(){
        return &_notEmpty;
    }
private:
    TaskQueue()
    :_notFull(_mutex),
    _notEmpty(_mutex)
    {}
    ~TaskQueue() {}
private:
    size_t _queSize;
    queue<int> _que;
    MutexLock _mutex;
    Condition _notFull;
    Condition _notEmpty;
    static TaskQueue * _pInstance;
    static pthread_once_t _once;
};
TaskQueue * TaskQueue::_pInstance=NULL;
pthread_once_t TaskQueue::_once=PTHREAD_ONCE_INIT;
}
