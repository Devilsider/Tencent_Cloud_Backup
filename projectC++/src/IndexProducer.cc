#include "DictProducer.h"
#include "IndexProducer.h"
#include "StringTrans.h"

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>

#include <iterator>
#include <functional>
#include <iostream>
#include <fstream>
#include <sstream>
using std::endl;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::distance;


namespace wd
{

void IndexProducer::read()
{
    ifstream ifs(_dictFilename);
    if(!ifs.is_open())
    {
        cout<<" open file "<<_dictFilename<<" error"<<endl;
        return;
    }
    string line;
    string word;
    int frequency;
    stringstream ss;
    while(getline(ifs,line)){
        ss.clear();
        ss.str("");
        ss<<line;
        /* cout<<" ss: "<<ss.str()<<endl; */
        ss>>word;
        ss>>frequency;
        _dict.push_back(std::make_pair(word,frequency));
    }
    ifs.close();
}

void IndexProducer::createENIndex()
{
    set<int> temp;
    //初始化索引unordered_map
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

    for(auto it=_dict.begin();it!=_dict.end();++it)
    {
        //将单词和在_dict中的下标值插入表中
        for(auto &c:it->first)
        {
            //冗余信息如何去除?
            //去重对应于查找候选词的操作
            //当查找候选词的时候，如果含i的该单词计算过
            //编辑距离，那么下次访问到相同单词的时候就
            //不在计算编辑距离，直接跳过，而确定该单词
            //是否被计算过就是通过bitmap来查看
            //按下标来计算index
            stringstream ss;
            string key;
            ss<<c;
            key=ss.str();
            auto itIndex=_index.find(key);
            /* cout<<"222 "<<endl; */
            if(itIndex!=_index.end()){
                itIndex->second.insert((int)distance(_dict.begin(),it)); 
            }
        }
    }
}

void IndexProducer::createCHIndex()
{
    StringTrans st;
    for(auto iter=_dict.begin();iter!=_dict.end();++iter)
    {
        wstring tmp =st.strToWstr(iter->first);
        int len=(int)tmp.size();
        for(int idx=0;idx<len;++idx)
        {
            //对中文中的每一汉字都建立索引
            string key;
            wstring ws=tmp.substr(idx,1);
            key=st.WstrToStr(ws);
            auto iterIndex=_index.find(key);
            if(iterIndex==_index.end())
            {
                //索引表中没有找到，新汉字插入表中
                set<int> temp;
                temp.insert((int)distance(_dict.begin(),iter));
                _index.insert(std::make_pair(key,temp));
            }
            else {
                //索引表中找到该字符
                iterIndex->second.insert((int)distance(_dict.begin(),iter));
            }
        }
    }
    
}

void IndexProducer::store(const string &filepath)
{
    //存储到data文件夹里面，文件名字为Index
    string indexFile(filepath);
    //新建立索引文件
    open(indexFile.c_str(),O_RDWR|O_CREAT,0666);
    ofstream ofs(indexFile);
    if(!ofs.is_open())
    {
        //是否正确打开
        cout<<" open file "<<indexFile<<" error"<<endl;
        return ;
    }
    for(auto &i:_index)
    {
        //按照格式 索引字母  下标1 下标2 下标3 下标4 ...... 格式排列
        ofs<<i.first<<" ";
        for(auto &c:i.second){
            ofs<<c<<" ";
        }
        ofs<<endl;
    }
    ofs.close();
    _dict.clear();
    _index.clear();
}

void IndexProducer::setDictFilename(const string & filename)
{
    _dictFilename=filename;
}
void IndexProducer::init()
{
    read();
    createENIndex();
    store("../dict/Index");
    
    setDictFilename("../dict/CNDictionary");
    read();
    createCHIndex();
    store("../dict/CNIndex");

}

void IndexProducer::showDict()
{
    //cout<<"IndexProducer::showDict"<<endl;
    for(auto &i:_dict)
    {
        cout<<"{word:"<<i.first<<","
            <<"frequency:"<<i.second<<"}"<<endl;
    }
}

void IndexProducer::showIndex()
{
    //测试
    for(auto & i :_index)
    {
        cout<<" "<<i.first<<" : ";
        for(auto &c:i.second){
            cout<<" "<<c;
        }
    cout<<endl;
    }
}

}//end of wd;


