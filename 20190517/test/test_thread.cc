#include "MutexLock.h"
#include "Condition.h"
#include <iostream>
using std::cout;
using std::endl;

int ticket=100;
bool flag=true;
wd::MutexLock mutex;
wd::Condition condition(mutex);

void *thread1(void *p){
    int cnt=20;
    while(cnt--){
        {
            /* cout<<"3"<<endl; */
            wd::MutexLockGuard autolock(mutex);
            if(false==flag){
                condition.wait();
            }
            --ticket;
            cout<<" sub_thread "<<pthread_self()<<" : "
                <<"ticket: "<<ticket<<endl;
            if(flag){
                flag=false;
            }
        }
        condition.notify();
    }
    /* cout<<"4"<<endl; */
    return NULL;
}

void *thread2(void *p){
    int cnt=20;
    while(cnt--){
        {
            /* cout<<"1"<<endl; */
            wd::MutexLockGuard autolock(mutex);
            if(true==flag){
                condition.wait();
            }
            --ticket;
            cout<<" sub_thread "<<pthread_self()<<" : "
                <<"ticket: "<<ticket<<endl;
            if(false==flag){
                flag=true;
            }
        }
        condition.notify();
    }
    /* cout<<"2"<<endl; */
    return NULL;
}


int main()
{
    pthread_t pthid1,pthid2;
    pthread_create(&pthid1,NULL,thread1,NULL);
    pthread_create(&pthid2,NULL,thread2,NULL);

    pthread_join(pthid1,NULL);
    pthread_join(pthid2,NULL);
    
    return 0;
}

