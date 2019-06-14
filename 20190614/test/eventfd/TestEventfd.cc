#include "EventfdThread.h"
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
        int number=::rand()%100;
        cout<<">> thread "<<pthread_self()
            <<": get a number = "<<number <<endl;
    }
};


int main()
{
    wd::EventfdThread eventfd(bind(&Mytask::process,Mytask()));
    eventfd.start();

    int cnt=20;
    while(cnt--)
    {
        cout<<" cnt == "<<cnt <<endl
            <<">> main thread notify sub thread to do something... "<<endl;
        eventfd.wakeup();
        ::sleep(1);
    }
    return 0;
}

