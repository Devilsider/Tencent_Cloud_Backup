#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <iostream>
using std::cout;
using std::endl;

template <typename  T,int sz = 10>
class Queue
{
public:
    Queue() 
    :_front(0),
    _rear(0),
    _queue(new T[sz]())
    {}
    
    bool empty(){
        return _rear==_front;
    }

    bool full(){
        return (_front==((_rear+1)%sz));
    }
    
    void enQueue(T elem){
        if(!full()){
            _queue[_rear]=elem;
            _rear=(_rear+1)%sz;
        }
        else{
            cout<<"queue is full!"<<endl;
            return;
        }
    }

    void deQueue()
    {
        if(!empty()){
            _front=(_front+1)%sz;
        }
        else{
            cout<<"queue is empty!"<<endl;
            return ;
        }
    }

    T getHead(){
        return _queue[_front];
    }

    T getTail(){
        return _queue[(_rear-1+sz)%sz];
    }

    void print(){
        for(int idx=0;idx<sz;++idx){
            cout<<" "<<_queue[idx];
        }
        cout<<endl;
    }
    ~Queue() {
        if(_queue){
            delete []_queue;
        }
    }

private:
    int _front;
    int _rear;
    T *_queue;
};

#endif
