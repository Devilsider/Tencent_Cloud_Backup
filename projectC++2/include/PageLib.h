#pragma once
#include "DirScanner.h"
#include "MySimhasher.h"

#include <map>
#include <string>
#include <vector>
#include <memory>
using std::string;
using std::map;
using std::vector;
using std::unique_ptr;

namespace wd
{
class PageLib
{
public:
    PageLib(DirScanner &dirscanner);
    void createFormatPageLib();//创建格式化网页库
    void createWebLib();//创建用offset读取的网页库
    void createOffsetLib(int docid,int offset, int length,const string & );//创建网页偏移库,网页序号，网页库偏移，长度
    void createNewLib();//创建去重后的lib
    void store();//存储formatPageLib,webLib,offsetLib

    bool isDuplicateWeb(const string &);//判断是否网页重复

    void setPmySimhasher(unique_ptr<MySimhasher> &p)
    {
        _PmySimhasher = std::move(p);
    }
private:
    DirScanner &_dirScanner;//目录扫描对象的引用
    vector<string> _vecFilefiles;//存放格式化后的网页容器
    map<int ,std::pair<int,int>> _offsetLib;//存放每篇网页库的位置信息
    vector<uint64_t> _vecSimhash;//辅助数据结构，存储所有网页的simhash
    unique_ptr<MySimhasher> _PmySimhasher;
};

}//end of wd
