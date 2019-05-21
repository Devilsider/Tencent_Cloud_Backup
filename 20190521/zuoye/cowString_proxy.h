#ifndef __CowString_H__
#define __CowString_H__
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
class CowString
{
public:
    CowString();
    CowString(const char *);
    CowString(const CowString &);
    //CowString &operator=(const CowString &);//使用代理类重载赋值操作符
    ~CowString();
    CowString& operator=(const CowString &);
    const  char * c_str()const{
    //返回字符串首地址
        return _pstr;
    }
    int size()const{
        //返回字符串长度
        return strlen(_pstr);
    }
    int refcount(){
        //返回引用计数
        return  *((int *)(_pstr-4));
    }
    const char & operator[](int idx)const{
        //只读，返回读取的字符
        return _pstr[idx];
    }
    
    class CharProxy{
    //代理类，用来区分读写
    public:
        CharProxy(int idx,CowString &rhs)
        :_idx(idx),
        _cowString(rhs)
        {
            cout<<"CharProxy(int,CowString&)"<<endl;
        }
        CharProxy &operator=(const char &ch);//执行写操作
        friend std::ostream &operator<<(std::ostream &os,const CharProxy &rhs);//执行读操作
    private:
        int _idx;
        CowString &_cowString;
    };
    CharProxy operator[](int idx){
            return CharProxy(idx,*this);
    }
private:
    void initRefCount(){
        *((int *)(_pstr-4))=1;
    }
    void increaseRefCount(){
        ++(*((int *)(_pstr-4)));
    }
    void decreaseRefCount(){
        --(*((int *)(_pstr-4)));
    }
    void release(){
        decreaseRefCount();
        if(0==refcount()){
            delete [](_pstr-4);
            cout<<"delete data"<<endl;
        }
    }
private:
    char * _pstr;
};

#endif


