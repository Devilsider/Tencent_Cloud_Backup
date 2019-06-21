#include "MyRedis.h"

#include <iostream>
#include <stdlib.h>
using std::cout;
using std::endl;
namespace wd
{
MyRedis * MyRedis::_pInstance = MyRedis::getInstance();

MyRedis * MyRedis::getInstance()
{
    if(_pInstance==NULL)
    {
        _pInstance = new MyRedis();
        atexit(destroy);
    }
    return _pInstance;
}
void MyRedis::destroy()
{
    if(_pInstance)
    {
        delete _pInstance;
    }
}

void MyRedis::init(const string &ip,size_t port)
{
    _mycli.connect(ip,port,
        [](const string &ip,size_t port,
           cpp_redis::client::connect_state status){
            if(status==cpp_redis::client::connect_state::dropped)
            {
                cout<<"client disconnected from "<<ip<<" : "<<port<<endl;
            }
        });
    //同步提交命令
    _mycli.sync_commit();
}

string MyRedis::get(const string &key)
{
    auto get = _mycli.get(key);
    _mycli.sync_commit();
    //同步提交命令 
    
    cpp_redis::reply res = get.get();

    if(res.is_null())
    {
        return "";
    }

    if(res.is_string())
    {
        return res.as_string();
    }
    return "";
}

void MyRedis::set(const string &key,const string &jsonStr)
{
    auto set = _mycli.set(key,jsonStr);
    _mycli.sync_commit();
    //同步提交命令 
    
    cpp_redis::reply res = set.get();
    
    if(res.is_null())
    {
        cout<<"set : "<<res<<",error"<<endl;
    }
}

}//end of wd
