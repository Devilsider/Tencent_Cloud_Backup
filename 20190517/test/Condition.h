#ifndef __WD_CONDITION_H__
#define __WD_CONDITION_H__
#include "MutexLock.h"
#include <pthread.h>
namespace wd{
class Condition
{
public:
    Condition(MutexLock &mutl) 
    :_mutexlock(mutl)
    {
        if(pthread_cond_init(&_cond,NULL)){
            perror("pthread_cond_init");
        }
    }
    Condition(const Condition &)=delete ;
    Condition &operator = (const Condition &)=delete ;
    void wait(){
        if(pthread_cond_wait(&_cond,_mutexlock.getMutexLockPtr())){
            perror("pthread_cond_wait");
        }
    }
    void notify(){
        if(pthread_cond_signal(&_cond)){
            perror("pthread_cond_signal");
        }
    }
    void notifyall(){
        if(pthread_cond_broadcast(&_cond)){
            perror("pthread_cond_broadcast");
        }
    }
    ~Condition() {
        if(pthread_cond_destroy(&_cond)){
            perror("pthread_cond_destroy");
        }
    }

private:
    pthread_cond_t _cond;
    MutexLock &_mutexlock;
};
}
#endif
