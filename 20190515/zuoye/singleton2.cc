#include <iostream>
using std::cout;
using std::endl;

class Singleton{
public:
  static  Singleton * getInstance(){
        /* pthread_mutex_lock(&_mutex); */
        if(NULL==_pInstance){
        /* pthread_mutex_unlock(&_mutex); */
            _pInstance = new Singleton();
        }
        /* pthread_mutex_unlock(&_mutex); */
        return _pInstance;
    }
  static  void destroy(){
        if(_pInstance){
            delete _pInstance;
            /* pthread_mutex_destroy(&_mutex); */
        }
    }
private:
    Singleton(){
        cout<<"I am Singleton()"<<endl;
        /* pthread_mutex_init(&_mutex,NULL); */
    }
    ~Singleton(){
        cout<<"I am ~Singleton()"<<endl;
    }
    static Singleton * _pInstance;
    /* static pthread_mutex_t _mutex; */
};
Singleton * Singleton::_pInstance=NULL;
/* pthread_mutex_t Singleton::_mutex; */
int main()
{
    /* Singleton s1; */
    Singleton *s2=Singleton::getInstance();
    Singleton *s3=Singleton::getInstance();
    cout<<"s2="<<s2<<endl
        <<"s3="<<s3<<endl;
    Singleton::destroy();
    return 0;
}

