#ifndef __SINGLETON_TEMPLATE_H__
#define __SINGLETON_TEMPLATE_H__

#include <stdlib.h>
#include <pthread.h>
#include <iostream>
using std::cout;
using std::endl;

template<typename T> 
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
    template<typename T1>
    static T * getInstance(T1 t){
        if(NULL==_pInstance) {
            _pInstance=new T(t);
            Singleton();
            atexit(destroy);
        }
        return  _pInstance;
    }
    template<typename... Args>
    static T * getInstance(Args... args){
        if(NULL==_pInstance) {
            /* cout<<" args num is "<<sizeof...(args)<<endl; */
            _pInstance=new T(args...);
            atexit(destroy);
        }
        return  _pInstance;
    }
    static void destroy(){
        cout<<" destroy() "<<endl;
        if(_pInstance){
            delete _pInstance;
        }
    }
    void print(){
        cout<<"_pInstance = "<<_pInstance<<endl;
    }
private:
    Singleton(){cout<<"Singleton()"<<endl;}
    ~Singleton(){cout<<"~Singleton()"<<endl;}
private:
    static T *_pInstance;
    static AutoRelease _autoRelease;
};
template<typename T>
T * Singleton<T>::_pInstance=NULL;
template<typename T>
typename Singleton<T>::AutoRelease Singleton<T>::_autoRelease=new AutoRelease();
#endif
