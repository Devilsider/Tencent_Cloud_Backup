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
            pthread_mutex_unlock(&_mutex);
            pthread_mutex_destroy(&_mutex);
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
    Condtion(){
        pthread_cond_init(&_cond,NULL);
        pthread_mutex_init(&_mutex,NULL);
    }
    Condtion(Condtion &con){
        _cond=con._cond;
        _mutex=con._mutex;
    }
    void wait()
    {
        pthread_mutex_lock(&_mutex);
        pthread_cond_wait(&_cond,&_mutex);
        pthread_mutex_unlock(&_mutex);
    }
    void notify(){
        pthread_cond_signal(&_cond);
    }
    void notifyall(){
        pthread_cond_broadcast(&_cond);
    }
    ~Condtion(){
        pthread_cond_destroy(&_cond);
    }
private:
    pthread_cond_t _cond;
    pthread_mutex_t _mutex;
};
typedef struct {
    MutexLock m;
    Condtion c;
    int abc;
}Data,*pData;
int num=10000000;
void *sigFuc(void *p){
    Data *pd=(Data *)p;
    /* sleep(3); */
    /* pd->m.lock(); */
    /* pd->abc=3; */
    /* cout<<"I am child thread,adb ="<<pd->abc<<endl; */
    /* cout<<"---------test mutex---------"<<endl; */
    /* pd->m.unlock(); */


    /* sleep(2); */
    /* pd->c.wait(); */
    /* pd->abc=11; */
    /* cout<<"I am child thread,abc= "<<pd->abc<<endl; */
    /* cout<<"---------test cond---------"<<endl; */
   
    /* sleep(2); */
    /* pd->c.wait(); */
    /* pd->abc=21; */
    /* cout<<"I am main thread ,abc="<<pd->abc<<endl; */
    /* cout<<"---------test broadcast---------"<<endl; */
    
        /* pd->m.lock(); */
    for(int idx=0;idx<num;++idx){
        pd->m.lock();
        ++pd->abc;
        pd->m.unlock();
    }
        /* pd->m.unlock(); */
    pthread_exit(NULL);
}
int main()
{
    Data data;
    data.abc=0;
    pthread_t threadId;
    pthread_create(&threadId,NULL,sigFuc,&data);
    /* sleep(3); */
    /* data.m.lock(); */
    /* data.abc=2; */
    /* cout<<"---------test mutex---------"<<endl; */
    /* cout<<"I am main thread ,abc ="<<data.abc<<endl; */
    /* data.m.unlock(); */


    /* sleep(3); */
    /* cout<<"---------test cond---------"<<endl; */
    /* data.abc=10; */
    /* cout<<"I am main thread ,abc="<<data.abc<<endl; */
    /* data.c.notify(); */
    

    /* sleep(3); */
    /* cout<<"---------test broadcast---------"<<endl; */
    /* data.abc=20; */
    /* cout<<"I am main thread ,abc="<<data.abc<<endl; */
    /* data.c.notifyall(); */
        /* data.m.lock(); */
    for(int idx=0;idx<num;++idx){
        data.m.lock();
        ++data.abc;
        data.m.unlock();
    }
        /* data.m.unlock(); */

    pthread_join(threadId,NULL);
    cout<<"abc is "<<data.abc<<endl;
    return 0;
}

