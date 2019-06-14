#include "TimerThread.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <functional>
#include <iostream>
using namespace std;

struct Mytask
{
    void process()
    {
        ::srand(::time(NULL));
        int number = ::rand()%100;
        cout<<">> thread"<<pthread_self()
            <<": get a number = "<<number<<endl;
    }
};

int main()
{
    wd::TimerThread timer(3,6,bind(&Mytask::process,Mytask())) ;
    timer.start();

    ::sleep(20);
    cout<<">> main thread timer stop..."<<endl;
    timer.stop();
    return 0;
}

