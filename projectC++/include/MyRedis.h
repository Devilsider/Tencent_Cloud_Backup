#pragma once
#include <cpp_redis/cpp_redis>

#include <iostream>
#include <string>
using std::string;
//单例对象
namespace  wd
{
class MyRedis
{
public:

    static MyRedis * getInstance();
    static void destroy();

    string get(const string &key);//使用库对象cpp_redis::get方法从redis获取数据
    //key为待查询候选词,在spellcorrectserver里面的
    void set(const string &key,const string &jsonStr);//使用库对象cpp_redis::set方法在redis中设置数据
    //key为查询的候选词,spellcorrectserver里面的，jsonStr为结果
    void init(const string &ip,size_t port);//redis地址和端口号

    cpp_redis::client & getMyredisClient(){
        return _mycli;
    }
private:
    MyRedis(){}
private:
    cpp_redis::client _mycli;
    static MyRedis * _pInstance;
};
}
