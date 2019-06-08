#include "Producer.h"
#include "Consumer.h"

#include <pthread.h>
#include <iostream>
#include <memory>
using namespace std;


int main()
{
    
    cout<<"main thread "<<pthread_self()<<endl;

    unique_ptr<wd::Thread> p(new wd::Producer());
    unique_ptr<wd::Thread> c(new wd::Consumer());
    p->start();
    c->start();
    
    c->join();
    p->join();
    return 0;
}

