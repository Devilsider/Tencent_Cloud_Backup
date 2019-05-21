#include<stdlib.h>
#include <iostream>
using std::cout;
using std::endl;

class Singleton1{
public:
    /* class AutoRelease{ */
    /* public: */
    /*     AutoRelease(){ */
    /*         cout<<"AutoRelease()"<<endl; */
    /*     } */
    /*     ~AutoRelease(){ */
    /*         cout<<"~AutoRelease()"<<endl; */
    /*         if(_pInstance){ */
    /*             delete _pInstance; */
    /*         } */
    /*     } */

    /* }; */
    static Singleton1 * getInstance(){
        if(NULL==_pInstance){
            _pInstance=new Singleton1();
            atexit(destroy);
        }
        return _pInstance;
    }
    void print(){
        cout<<"_pInstance = "<<_pInstance<<endl;
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
    /* static AutoRelease autoRelease; */
};
Singleton1 * Singleton1::_pInstance=getInstance();
/* Singleton1::AutoRelease Singleton1::autoRelease; */
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

