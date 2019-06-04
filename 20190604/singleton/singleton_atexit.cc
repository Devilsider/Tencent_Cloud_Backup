#include <cstdlib>
#include <iostream>
using namespace std;

class Singleton{
public:
    static Singleton * getInstance(){
        if(NULL==_pInstance){
            _pInstance=new Singleton();
            atexit(init);
        }
        return _pInstance;
    }
    static void destroy(){
        if(_pInstance){
            delete _pInstance;
        }
        cout<<"destroy()"<<endl;
    }
    static void init(){
        destroy();
    }
    void print(){
        cout<<" _pInstance= "<<_pInstance<<endl;
    }
private:
    Singleton(){
        cout<<"Singleton()"<<endl;
    }
    ~Singleton(){
        cout<<"~Singleton()"<<endl;
    }
    static Singleton *_pInstance;
};
Singleton * Singleton::_pInstance=Singleton::getInstance();
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

