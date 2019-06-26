#pragma once
#include "MyPage.h"
#include "MyWebPage.h"
#include "Jieba.hpp"

#include <vector>
#include <string>
#include <set>
#include <unordered_map>

using std::string;
using std::vector;
using std::set;
using std::unordered_map;
namespace  wd
{

class InvertIndex
{
public:
    void read(const string &,const string &);//将所有网页读入vector,网络库的路径和偏移库的路径
    void createInvertIndex();//生成倒排索引表
    void store(const string &);//生成的倒排索引表存储到磁盘
private:
    vector<MyWebPage> _allMyWeb;//存放所有的网页内容
    unordered_map<string ,int> _wordCount;//包含该单词的文档数df
    unordered_map<string,set<std::pair<int,double>>> _invertIndex;
};

}
