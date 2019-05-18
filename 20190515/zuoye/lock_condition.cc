#include <unistd.h>
#include <iostream>
using std::cout;
using std::endl;
class MutexLock{
    public :
        MutexLock(){
            pthread_mutex_init(&_mutex,NULL);
        }
        MutexLock(pthread_mutex_t mut){
           _mutex=mut;
        }
        ~MutexLock(){
            pthread_mutex_destroy(&_mutex);
        }
        pthread_mutex_t * getMutex(){
            return &_mutex;
        }
        void lock(){
            pthread_mutex_lock(&_mutex);
        }
        void unlock()
        {
            pthread_mutex_unlock(&_mutex);
        }
    private:
        pthread_mutex_t _mutex;
};
class Condtion{
public:
    Condtion(MutexLock &muL)
    :_mutexLock(muL)
    {
        if(pthread_cond_init(&_cond,NULL)){
            perror("pthread_cond_init");
        }
    }
    void wait()
    {
        if(pthread_cond_wait(&_cond,_mutexLock.getMutex())){
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
    ~Condtion(){       
        if(pthread_cond_destroy(&_cond)){
            perror("pthread_cond_destroy");
        }
    }
private:
    pthread_cond_t _cond;
    MutexLock &_mutexLock;
};
typedef struct {
    MutexLock m;
    Condtion c;
    int abc;
}Data,*pData;
void *sigFuc(void *p){
    Data *pd=(Data *)p;
    sleep(3);
    pd->m.lock();
    pd->abc=3;
    cout<<"I am child thread,adb ="<<pd->abc<<endl;
    cout<<"---------test mutex---------"<<endl;
    pd->m.unlock();


    sleep(2);
    pd->c.wait();
    pd->abc=11;
    cout<<"I am child thread,abc= "<<pd->abc<<endl;
    cout<<"---------test cond---------"<<endl;
   
    sleep(2);
    pd->c.wait();
    pd->abc=21;
    cout<<"I am main thread ,abc="<<pd->abc<<endl;
    cout<<"---------test broadcast---------"<<endl;
    
    pthread_exit(NULL);
}
int main()
{
    Data data;
    data.c(&m);
    data.abc=1;
    pthread_t threadId;
    pthread_create(&threadId,NULL,sigFuc,&data);
    sleep(3);
    data.m.lock();
    data.abc=2;
    cout<<"---------test mutex---------"<<endl;
    cout<<"I am main thread ,abc ="<<data.abc<<endl;
    data.m.unlock();


    sleep(3);
    cout<<"---------test cond---------"<<endl;
    data.abc=10;
    cout<<"I am main thread ,abc="<<data.abc<<endl;
    data.c.notify();
    

    sleep(3);
    cout<<"---------test broadcast---------"<<endl;
    data.abc=20;
    cout<<"I am main thread ,abc="<<data.abc<<endl;
    data.c.notifyall();


    pthread_join(threadId,NULL);
    return 0;
}

