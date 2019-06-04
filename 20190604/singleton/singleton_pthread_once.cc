#include <pthread.h>
#include <cstdlib>
#include <iostream>
using namespace std;

class Singleton{
public:
    static Singleton * getInstance(){
        pthread_once(&_once,init);
        return _pInstance;
    }
    static void destroy(){
        if(_pInstance){
            delete _pInstance;
        }
        cout<<"destroy()"<<endl;
    }
    void print(){
        cout<<" _pInstance= "<<_pInstance<<endl;
    }
    static void init(){
        _pInstance=new Singleton();
        atexit(destroy);
    }
private:
    Singleton(){
        cout<<"Singleton()"<<endl;
    }
    ~Singleton(){
        cout<<"~Singleton()"<<endl;
    }
private:
    static Singleton *_pInstance;
    static pthread_once_t _once;
};
Singleton * Singleton::_pInstance=NULL;
pthread_once_t Singleton::_once=PTHREAD_ONCE_INIT;
int main()
{
    Singleton *s1=Singleton::getInstance() ;
    Singleton *s2=Singleton::getInstance() ;
    Singleton *s3=Singleton::getInstance() ;
    
    s1->print();
    s2->print();
    s3->print();

    /* s1->destroy(); */
    return 0;
}

