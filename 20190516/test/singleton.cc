#include <iostream>
using std::cout;
using std::endl;
class Singleton{
public:
    static Singleton * getInstance(){
        if(nullptr==_pInstance){
            _pInstance=new Singleton();
        }
        return _pInstance;
    }
    static void destory(){
        if(_pInstance){
            delete _pInstance;
        }
    }
    void print(){
        cout<<"_pInstance = "<<_pInstance<<endl;
    }
private:
    Singleton(){
        cout<<"I am Singleton()"<<endl;
    }
    ~Singleton(){
        cout<<"I am ~Singleton()"<<endl;
    }
    static Singleton *_pInstance;
};
Singleton * Singleton::_pInstance=nullptr;
int main()
{
    Singleton *s1=Singleton::getInstance();
    Singleton *s2=Singleton::getInstance();
    Singleton *s3=Singleton::getInstance();
    s1->print();
    s2->print();
    s3->print();
    s1->destory();
    return 0;
}

