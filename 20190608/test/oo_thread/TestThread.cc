#include "Noncopyable.h"
#include "Thread.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <memory>
#include <iostream>
using namespace std;

class Mythread:public wd::Thread
{
public:
    ~Mythread(){
        cout<<"~Mythread()"<<endl;
    }
private:
    void run()override
    {
        ::srand(::clock());
        int cnt=10;
        while(cnt--){
            int number=::rand()%100;
            cout<<"sub thread "<<pthread_self()
                <<" : get a number "<<number<<endl;
            ::sleep(1);
        }
    }
};

int main(void)
{
    cout<<">> main thread "<<pthread_self()<<endl;
    
    unique_ptr<wd::Thread> mythread(new Mythread());
    mythread->start();
    mythread->join();
    return 0;
}

