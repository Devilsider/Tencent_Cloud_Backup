#include "Consumer.h"
#include "TaskQueue.h"
#include <unistd.h>
#include <cstdlib>
#include <iostream>
using  namespace std;

namespace wd{

void Consumer::get(TaskQueue &taskque)
{
    int cnt=10;
    while(cnt--){
        int number=taskque.pop();
        cout<<"Consumer sub thread "<<pthread_self()
            <<">> Consumer get a number "<<number<<endl;
        ::sleep(2);
    }
}

}
