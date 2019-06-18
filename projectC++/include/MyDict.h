#pragma once
#include <stdlib.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <set>
using std::vector;
using std::unordered_map;
using std::set;
using std::string;

namespace wd
{

class MyDict
{
public:
    static MyDict * getInstance()
    {
        if(NULL==_pInstance)
        {
            _pInstance = new MyDict();
            atexit(destroy);
        }
        return _pInstance;
    }
    static void destroy()
    {
        if(_pInstance)
        {
            delete _pInstance;
        }
    }
    unordered_map<string,set<int>> &getIndex()
    {
        return _index;
    }
    vector<std::pair<string,int>> &getDict()
    {
        return _dict;
    }


    void init(const string &filepath);//设置词典和索引的路径并且初始化他们
    void showDict();//测试用
    void showIndex();//测试用
private:
    MyDict()
    {}

private:
    string _filepath;
    vector<std::pair<string,int>> _dict;//从离线文件中将词典内容读出来到vector中
    unordered_map<string,set<int>> _index;//从离线文件中将索引内容读到index中
    static MyDict * _pInstance;
};

}//end of namespace
