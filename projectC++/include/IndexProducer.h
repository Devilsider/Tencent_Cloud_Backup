#pragma once
#include "DictProducer.h"

#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>
#include <sstream>
using std::vector;
using std::unordered_map;
using std::set;
using std::stringstream;
using std::cout;
using std::endl;

namespace wd
{

class IndexProducer
{
public:
    IndexProducer(const string &dictfilename)
    :_dictFilename(dictfilename)
    {}
    

    unordered_map<string,set<int>> & getIndex()
    {
        return _index;
    }
    vector<std::pair<string,int>> &getDict()
    {
        return _dict;
    }
    

    void read();//将dict词典内容读到_dict中
    void createENIndex();//生成a~z的索引的单词
    void createCHIndex();//生成中文词典

    void init();//包含read()和createIndex()
    void store(const string &);//存储到文件
    void setDictFilename(const string &);//设置词典的路径
    void showDict();//测试用
    void showIndex();//测试用
private:
    string _dictFilename;//dict词典的绝对路径
    vector<std::pair<string,int>>  _dict;//将词典内容读出来读到vector中
    unordered_map<string,set<int>> _index;//存放a~z的索引的单词
};

}
