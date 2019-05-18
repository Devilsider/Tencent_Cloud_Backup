#include <iostream>
using std::cout;
using std::endl;
class Singleton{
    public:
        static Singleton * getInstance(){
            cout<<"getInstance"<<endl;
            if(NULL==_pInstance){
                _pInstance=new Singleton();
            }
            return _pInstance;
        }
        static void destory(){
            cout<<"destory"<<endl;
            if(_pInstance){
                delete _pInstance;
                _pInstance=NULL;
            }
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
Singleton *Singleton::_pInstance=NULL;


int main()
{   
    Singleton* s1=Singleton::getInstance();
    Singleton* s2=Singleton::getInstance();
    Singleton* s3=Singleton::getInstance();
    /* Singleton s5; */ 
    /* Singleton s4=new Singleton(); */
    cout<<"s1 address= " <<s1<<endl
        <<"s2 address= " <<s2<<endl
        <<"s3 address= " <<s3<<endl;
    Singleton::destory();
    return 0;
}

