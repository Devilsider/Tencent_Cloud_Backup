#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
class Singleton{
public:
    static Singleton * getInstance(){
        if(nullptr==_pInstance){
            _pInstance=new Singleton();
        }
        return  _pInstance;
    }
    void destroy(){
        if(_pInstance){
            delete _pInstance;
        }
    }
    void print(){
        cout<<"_pInstance is "<<_pInstance<<endl;
    }
private:
    Singleton(){
        cout<<"I am  Singleton()"<<endl;
    }
    ~Singleton(){
       cout<<"I am ~Singleton()" <<endl;
        /* if(_pInstance){ */
        /*     delete _pInstance; */
        /* } */
    }
static Singleton * _pInstance;
};
Singleton * Singleton::_pInstance=nullptr;
int main()
{
    Singleton * s1=Singleton::getInstance();
    s1->print();
    Singleton * s2=Singleton::getInstance();
    s2->print();
    Singleton * s3=Singleton::getInstance();
    s3->print();
    s1->destroy();
    return 0;
}

