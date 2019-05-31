#ifndef __MYVECTOR_H__
#define __MYVECTOR_H__
#include <memory>
#include <iostream>
using namespace std;

template<typename T>
class Myvector{
public:
    typedef T value_type;
    typedef T *pointer;
    typedef T *iterator;
    typedef const T *const_iterator;

    Myvector()
    :_start(NULL),_finish(NULL),_end_of_storage(NULL)
    {}

    size_t size()const {
        return _finish-_start;
    }
    size_t capacity()const {
        return _end_of_storage-_start;
    }

    void push_back(const T &t);
    void pop_back();

    const_iterator begin()const{
        return _start;
    }
    const_iterator end()const{
        return _finish;
    }

    T & operator[](size_t idx)const{
        return _start[idx];
    }

private:
    void reallocate();
private:
    static allocator<T> _alloc;
    T *_start;
    T *_finish;
    T *_end_of_storage;

};

template<typename T>
allocator<T> Myvector<T>::_alloc;

template<typename T>
void Myvector<T>::push_back(const T &t){
    if(size()==capacity()){
        reallocate();
    }

    _alloc.construct(_finish++,t); //对象的构造
}

template<typename T>
void Myvector<T>::pop_back(){
    if(size()>0){
        _alloc.destroy(--_finish);
    }
}

template<typename T>
void Myvector<T>::reallocate(){
    size_t oldspace=capacity();
    size_t newspace=2*oldspace > 0? 2*oldspace : 1;

    T *ptemp=_alloc.allocate(newspace);
    if(_start){
        uninitialized_copy(_start,_finish,ptemp);

        while(_finish != _start){
            _alloc.destroy(--_finish);
        }
        _alloc.deallocate(_start,oldspace);
    }

    _start=ptemp;
    _finish=_start+oldspace;
    _end_of_storage=_start+newspace;
}


#endif
