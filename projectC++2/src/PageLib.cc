#include "MyReaderXML.h"
#include "PageLib.h"
#include "tinyxml2.h"

#include <fstream>
#include <iostream>
using std::ofstream;
using std::ifstream;

namespace wd
{

PageLib::PageLib(DirScanner &dirscanner)
:_dirScanner(dirscanner)
{}

void PageLib::createFormatPageLib()
{   
    MyReaderXML readerXML;
    auto  vec = _dirScanner.getFile();
    for(auto iter = vec.begin();iter!=vec.end();++iter)
    {
        readerXML.parseRss(*iter);
    }
    readerXML.dump("../pagelib/pagelib.xml");
}

void PageLib::createWebLib()
{
    MyReaderXML readerXML;
    readerXML.parseDoc("../pagelib/pagelib.xml");
    _vecFilefiles = readerXML.getVecFilesfile();//获取字符串化网页
}

void PageLib::createOffsetLib(int docid,int offset,int len)
{
    ofstream ofs("../pagelib/offset.lib",std::ios::app);
    if(!ofs.is_open())
    {
        cout<<"ofs open file "<<"offset.lib error"<<endl;
    }
    ofs<<docid<<" "<<offset<<" "<<len<<endl;
}

void PageLib::store()
{
    //存储webLib的同时生成网页偏移库
    ofstream ofs("../pagelib/webpage.lib",std::ios::app);
    if(!ofs.is_open())
    {
        cout<<"ofs open file "<<" webpage.lib error"<<endl;
    }
    int idx=1;
    for(auto iter = _vecFilefiles.begin();iter!=_vecFilefiles.end();++iter)
    {
        int docid = idx; 
        int offset = ofs.tellp();//偏移量
        int len = iter->size();//string 长度
        ofs<<*iter;
        createOffsetLib(docid,offset,len);
        idx++;
    }
}

}//end of namespace

