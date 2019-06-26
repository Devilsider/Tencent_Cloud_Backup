#pragma once
#include <stdlib.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <set>
using std::cout;
using std::endl;
using std::unordered_map;
using std::string;
using std::set;
using std::vector;
using std::ifstream;

namespace wd
{

class MyLibFile
{
public:
    //单例对象
    static MyLibFile * getInstance()
    {
        if(_pInstance == NULL)
        {
            _pInstance = new MyLibFile();
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
    unordered_map<int,std::pair<int,int>> &getOffset()
    {
        return _offset;
    }
    unordered_map<string,set<std::pair<int,double>>> &getInvertIndex()
    {
        return _invertIndex;
    }
    string &getWebPageFile(){
        return _webPageFile;
    }
    void setWebPageFile(const string & s)
    {
        _webPageFile = s;
    }
    void read(const string &webPageFile,const string &offset,const string &invertIndex);//将网页偏移库，倒排索引库都读入进来，还有初始化网页库文件路径
    void showOffset();//测试用
    void showInvertIndex();//测试用
private: 
    MyLibFile(){} 
    ~MyLibFile(){}
private:
    static MyLibFile * _pInstance;
    string _webPageFile;//网页库文件路径
    unordered_map<int,std::pair<int,int>> _offset;//网页偏移表
    unordered_map<string,set<std::pair<int,double>>> _invertIndex;//倒排索引表
};

}
