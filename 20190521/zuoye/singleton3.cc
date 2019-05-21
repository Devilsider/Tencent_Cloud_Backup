#include<stdlib.h>
#include <pthread.h>
#include <iostream>
using std::cout;
using std::endl;

class Singleton1{
public:
    static Singleton1 * getInstance(){
        pthread_once(&_once,init);
        return _pInstance;
    }
    void print(){
        cout<<"_pInstance = "<<_pInstance<<endl;
    }
    static void init(){
        _pInstance=new Singleton1();
        atexit(destroy);
    }
    static void destroy(){
        cout<<"destroy()"<<endl;
        if(_pInstance){
            delete _pInstance;
        }
    }
private:
    Singleton1(){cout<<"Singleton1()"<<endl;}
    ~Singleton1(){cout<<"~Singleton1()"<<endl;}

    static Singleton1 *_pInstance;
    static pthread_once_t _once;
};
Singleton1 * Singleton1::_pInstance=NULL;
pthread_once_t Singleton1::_once=PTHREAD_ONCE_INIT;
int main()
{
    Singleton1 *s1=Singleton1::getInstance();
    Singleton1 *s2=Singleton1::getInstance();
    Singleton1 *s3=Singleton1::getInstance();

    s1->print();
    s2->print();
    s3->print();


    return 0;
}

