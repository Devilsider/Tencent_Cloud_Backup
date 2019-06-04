#include <iostream>
using namespace std;

class Singleton{
public:
    class AutoRelease{ 
    public:
        AutoRelease(){
            cout<<"AutoRelease()"<<endl;
        }
        ~AutoRelease(){
            cout<<"~AutoRelease()"<<endl;
            if(_pInstance){
                delete _pInstance;
            }
        }
    };
    static Singleton * getInstance(){
        if(NULL==_pInstance){
            _pInstance=new Singleton();
        }
        return _pInstance;
    }
    void destroy(){
        if(_pInstance){
            delete _pInstance;
        }
        cout<<"destroy()"<<endl;
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
private:
    static Singleton *_pInstance;
    static AutoRelease _autoRelease;
};
Singleton * Singleton::_pInstance=NULL;
Singleton::AutoRelease Singleton::_autoRelease;
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

