#include <stdlib.h>
#include <iostream>
using std::cout;
using std::endl;

class Singleton{
public:
    /* class AutoRelease{ */
    /* public: */
    /*     AutoRelease(){ */
    /*         cout<<"AutoRelease()"<<endl; */
    /*     } */
    /*     ~AutoRelease(){ */
    /*         cout<<"~AutoRelease()"<<endl; */
    /*         if(_pInstance){ */
    /*             delete  _pInstance; */
    /*         } */
    /*     } */
    /* }; */
    static Singleton * getInstacne(){
        if(NULL==_pInstance){
            _pInstance=new Singleton();
            atexit(destroy);
        }
        return  _pInstance;
    }
    static void destroy(){
        if(_pInstance){
            delete _pInstance;
        }
    }
    void print(){
        cout<<"_pInstance = "<<_pInstance<<endl;
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
    /* static AutoRelease autoRelease; */
};
Singleton * Singleton::_pInstance=getInstacne();
/* Singleton::AutoRelease Singleton::autoRelease; */
int main()
{
    Singleton *s1=Singleton::getInstacne();
    Singleton *s2=Singleton::getInstacne();
    Singleton *s3=Singleton::getInstacne();
    s1->print();
    s2->print();
    s3->print();

    

    return 0;
}

