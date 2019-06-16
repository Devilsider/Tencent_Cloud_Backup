#pragma once
#include "DictProducer.h"
#include "BitMap.h"

#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>
#include <sstream>
using std::vector;
using std::unordered_map;
using std::set;
using std::stringstream;

namespace wd
{

class IndexProducer
{
public:
    IndexProducer(const string &dictfilename)
    :_dictFilename(dictfilename),
    _bitmap(10000)
    {
        set<int> temp;
        //初始换索引unordered_map
        for(int idx=97;idx<123;++idx) 
        {
            char ch=idx;
            /* std::cout<<" "<<ch<<std::endl; */
            string tmpstr;
            stringstream ss;
            ss<<ch;
            tmpstr=ss.str();
            _index.insert(std::make_pair(tmpstr,temp));
        }
        
    }
    unordered_map<string,set<int>> * getIndex()
    {
        return &_index;
    }
    BitMap * getBitMap() 
    {
        return & _bitmap;
    }

    void read();//将dict词典内容读到_dict中
    void createIndex();//生成a~z的索引的单词
    void init();//包含read()和createIndex()
    void showDict();//测试用
    void showIndex();//测试用
private:
    string _dictFilename;//dict词典的绝对路径
    vector<std::pair<string,int>>  _dict;//将词典内容读出来读到vector中
    unordered_map<string,set<int>> _index;//存放a~z的索引的单词
    BitMap _bitmap;//使用位图去除冗余数据
};

}
