#pragma once
#include "BitMap.h"

#include <stdio.h>
#include <pthread.h>

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <memory>
#include <set>
using std::cout;
using std::string;
using std::vector;
using std::endl;
using std::unordered_map;
using std::unique_ptr;
using std::set;
namespace wd
{
class Mydict
{
public:
    //单例模式
    static Mydict * getInstance()
    {
        pthread_once(&_once,init);
        return _pInstance;
    }
    static void init()
    {
        _pInstance=new Mydict();
        atexit(destroy);
    }
    static void destroy()
    {
        if(_pInstance)
        {
            delete _pInstance;
        }
    }
    void print(){
        cout<<" _pInstance = "<<_pInstance<<endl;
    }
    void setDict(unique_ptr<vector<std::pair<string,int>>> pdict)
    {
        _pdict=move(pdict);
    }
    void setIndex(unique_ptr<unordered_map<string,set<int>>> pindex)
    {
        _pindex=move(pindex);
    }
    void setBitMap(unique_ptr<BitMap> pbitmap)
    {
        _pbitMap=move(pbitmap);
    }

    void start(unique_ptr<vector<std::pair<string,int>>>  pdict,
               unique_ptr<unordered_map<string,set<int>>> pindex,
           unique_ptr<BitMap>  pbitmap)
    {

    }

    
private:
    Mydict()
    {}
    ~Mydict() {}
private:
    static Mydict * _pInstance;
    static pthread_once_t _once;
    unique_ptr<vector<std::pair<string , int >>> _pdict;
    unique_ptr<unordered_map<string,set<int>>> _pindex;
    unique_ptr<BitMap> _pbitMap;
};
Mydict * Mydict::_pInstance=NULL;
pthread_once_t Mydict::_once=PTHREAD_ONCE_INIT;
}
