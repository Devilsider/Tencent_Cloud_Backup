#include "Thread.h"
#include "TaskQueue.h"
#include "Producer.h"
#include "Consumer.h"

#include <unistd.h>
#include <cstdlib>
#include <time.h>
#include <memory>
#include <iostream>



class Mytask{
public:
    ~Mytask(){
        cout<<"~Mytask()"<<endl;
    }

    void process(){
        ::srand(clock());
        int cnt=10;
        while(cnt--){
            int number=::rand()%100;
            cout<<"sub thread "<<pthread_self()
                <<": get a number = "<<number<<endl;
            ::sleep(1);
        }
    }
};


int main()
{
    cout<<">> main thread "<<pthread_self()<<endl;

    wd::TaskQueue taskque;//

    unique_ptr<wd::Thread> producer1(new wd::Thread(std::bind(&wd::Producer::create,
                            wd::Producer(),ref(taskque)))) ;
    unique_ptr<wd::Thread> producer2(new wd::Thread(std::bind(&wd::Producer::create,
                            wd::Producer(),ref(taskque)))) ;
    unique_ptr<wd::Thread> consumer1(new wd::Thread(std::bind(&wd::Consumer::get,
                            wd::Consumer(),ref(taskque)))) ;
    unique_ptr<wd::Thread> consumer2(new wd::Thread(std::bind(&wd::Consumer::get,
                            wd::Consumer(),ref(taskque)))) ;


    producer1->start();
    producer2->start();
    consumer1->start();
    consumer2->start();

    producer1->join();
    producer2->join();
    consumer1->join();
    consumer2->join();
    return 0;
}

