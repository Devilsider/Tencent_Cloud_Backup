#include "MyReaderXML.h"
#include "PageLib.h"
#include "tinyxml2.h"

#include <fstream>
#include <iostream>
#include <sstream>
using std::ofstream;
using std::ifstream;
using std::stringstream;

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
    readerXML.dump("../../pagelib/pagelib.xml");
}

void PageLib::createWebLib()
{
    _vecFilefiles.clear();
    MyReaderXML readerXML;
    readerXML.parseDoc("../../pagelib/pagelib.xml");
    _vecFilefiles = readerXML.getVecFilesfile();//获取字符串化网页
}

void PageLib::createOffsetLib(int docid,int offset,int len,const string & path)
{
    ofstream ofs(path,std::ios::app);
    if(!ofs.is_open())
    {
        cout<<"ofs open file "<<"offset.lib error"<<endl;
    }
    ofs<<docid<<" "<<offset<<" "<<len<<endl;
}

void PageLib::store()
{
    //存储webLib的同时生成网页偏移库
    ofstream ofs("../../pagelib/webpage.lib",std::ios::app);
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
        createOffsetLib(docid,offset,len,"../../pagelib/offset.lib");
        idx++;
    }
}

void PageLib::createNewLib()
{
    ifstream ifsWebLib("../../pagelib/webpage.lib");
    ifstream ifsOffset("../../pagelib/offset.lib");
    ofstream ofsNewOffset("../../pagelib/new_offset.lib",std::ios::app);//去重后
    
    string line; 
    while(getline(ifsOffset,line))
    {   
        stringstream ss;
        string web;
        char buff[65536];
        int docid,offset,len;
        ss<<line;
        ss>>docid>>offset>>len;
        ifsWebLib.seekg(offset,ifsWebLib.beg);
        ifsWebLib.read(buff,len);
        web = buff;
        if(isDuplicateWeb(web))
        {
            //不写入new_offset.lib
        }else{
            //写入new_offset.lib
            ofsNewOffset<<docid<<" "<<offset<<" "<<len<<endl;
        }
    }
}

bool PageLib::isDuplicateWeb(const string &web)
{
    uint64_t simhash;
    size_t keyWordNum = 5;
    _PmySimhasher.get()->getMySimhasher().make(web,keyWordNum,simhash);
    for(auto iter = _vecSimhash.begin();iter!= _vecSimhash.end();++iter)
    {
        if(_PmySimhasher.get()->getMySimhasher().isEqual(*iter,simhash))
        {
            //网页重复
            return true;
        }
    }
    //没有找到，即不重复，更新_vecSimhash
    _vecSimhash.push_back(simhash);
    return false;
}

}//end of namespace

