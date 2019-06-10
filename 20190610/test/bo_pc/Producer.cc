#include "Producer.h"

#include "TaskQueue.h"

#include <unistd.h>
#include <cstdlib>
#include <iostream>
using namespace std;

namespace wd{

void Producer::create(TaskQueue & taskque){
    ::srand(::clock());
    int cnt=10;
    while(cnt--){
        int number=::rand()%100;
        taskque.push(number);
        cout<<">>Producer sub thread "<<pthread_self()
            <<"Producer create  a  number = "<<number<<endl;
        sleep(1);
    }
}

}
