#include "Thread.h"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <memory>
#include <iostream>
using namespace std;

class MyTask
{
public:
    ~MyTask(){
        cout<<"~MyTask()"<<endl;
    }
    
    void process(){
        ::srand(::clock());
        int cnt = 10;
        while(cnt--){
            int number = ::rand()%100;
            cout<<"sub thread "<<pthread_self()
                <<": get a number "<<number<<endl;

            ::sleep(1);
        }
    }

    
};

int main()
{
    cout<<">> main thread" <<pthread_self()<<endl;
    MyTask task;

    unique_ptr<wd::Thread> mythread(
            new wd::Thread(std::bind(&MyTask::process,task)));
    mythread->start();
    mythread->join();
    return 0;
}

