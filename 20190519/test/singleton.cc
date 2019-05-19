#include <iostream>
using std::cout;
using std::endl;

class Singleton{
public:
    static Singleton *getInstance(){
        if(NULL==_pInstance){
            _pInstance=new Singleton();
        }
        return _pInstance;
    }
    void destroy(){
        if(_pInstance){
            delete _pInstance;
        }
    }
    void print(){
        cout<<" _pInstance = "<<_pInstance<<endl;
    }
private:
    Singleton(){
        cout<<"I am  Singleton()"<<endl;

    }
    ~Singleton(){
        cout<<"I am ~Singleton()"<<endl;
    }
    static Singleton *_pInstance;
};
 Singleton* Singleton::_pInstance=NULL;
int main()
{
   /* Singleton s1; */
    Singleton *s2=Singleton::getInstance();
    Singleton *s3=Singleton::getInstance();

    s2->print();
    s3->print();
    s2->destroy();
    return 0;
}

