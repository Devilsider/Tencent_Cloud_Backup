#include "Threadpool.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>

using namespace std;

class Mytask
:public wd::Task
{
public:
    void process(){
        ::srand(time(NULL));
        int number = rand()%100;

        cout<<">>sub thread "<<pthread_self()
            <<"create a number "<<number<<endl;

        sleep(1);
    }
};
int main()
{
    wd::Threadpool threadpool(4,10);
    threadpool.start();
    unique_ptr<wd::Task> task(new Mytask());

    int cnt=20;
    while(cnt--){
        threadpool.addTask(task.get());
    }
    threadpool.stop();
    return 0;
}

