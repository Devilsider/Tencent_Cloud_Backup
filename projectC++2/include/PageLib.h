#pragma once
#include "DirScanner.h"
#include <map>
#include <string>
#include <vector>
using std::string;
using std::map;
using std::vector;

namespace wd
{
class PageLib
{
public:
    PageLib(DirScanner &dirscanner);
    void createFormatPageLib();//创建格式化网页库
    void createWebLib();//创建用offset读取的网页库
    void createOffsetLib();//创建网页偏移库
    void store();//存储formatPageLib,webLib,offsetLib
private:
    DirScanner &_dirScanner;//目录扫描对象的引用
    vector<string> _vecFilefiles;//存放格式化后的网页容器
    map<int ,std::pair<int,int>> _offsetLib;//存放每篇网页库的位置信息
};

}//end of wd
