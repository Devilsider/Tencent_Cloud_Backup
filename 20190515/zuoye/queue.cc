#include <iostream>
using std::cout;
using std::endl;

class Queue{
//数组队列，不是链队
public:
    Queue(){
        cout<<"I am Queue"<<endl;
        _front=_rear=0;
        _queueMaxSize=100;
        _queue=new int[_queueMaxSize];
    }
    Queue(int size){
        _front=_rear=0;
        cout<<"I am QueueSize"<<endl;
        _queueMaxSize=size;
        _queue=new int[_queueMaxSize];
    }
    bool empty(){
        if(_rear==_front){
            return true;
        }
        return false;
    }
    bool full(){
        if((_rear+1)%_queueMaxSize==_front){
            return true;
        }
        return false;
    }
    void enqueue(int elem){
        //入队
        if(!full()){
            //未满
            _queue[_rear]=elem;
            _rear=(_rear+1)%_queueMaxSize;
        }
        else{
            cout<<"queue is full!"<<endl;
        }
    }
    void dequeue(){
        if(!empty()){
            _queue[_front]=0;
            _front=(_front+1)%_queueMaxSize;
        }
        else{
            cout<<"queue is empty!"<<endl;
        }
    }
    int front(){
        if(!empty()){
            return _queue[_front];
        }
        return -1;
    }
    int back(){
        if(!empty()){
            return _queue[(_rear-1+_queueMaxSize)%_queueMaxSize];
        }
        return -1;
    }
    void print(){
        int idx=_front;
        if(empty()){
            cout<<"queue is empty"<<endl;
        }
        while(idx!=_rear){
            cout<<"queue[idx]= "<<_queue[idx]<<endl;
            idx=(idx+1)%_queueMaxSize;
        }
    }
    ~Queue(){
        delete []_queue;
    }
    int getQueueSize(){
        return _queueMaxSize;
    }
private:
    int _queueMaxSize;
    int *_queue;//开辟队列数组空间
    int _front;
    int _rear;
};
int main()
{
    Queue q1;
    Queue q2(10);
    q2.dequeue();
    q1.dequeue();
    for(int idx=0;idx<12;++idx){
        q2.enqueue(idx);
    }
    q2.print();
    int elem;
    elem=q2.front();
    cout<<"elem.front = "<<elem<<endl;
    elem=q2.back();
    cout<<"elem.back = "<<elem<<endl;
    for(int idx=0;idx<12;++idx){
        q2.dequeue();
    }
    q2.print();
    return 0;
}

