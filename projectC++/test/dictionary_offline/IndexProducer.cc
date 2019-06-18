#include "/home/ubuntu/projectC++/include/IndexProducer.h"

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>

#include <iterator>
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
/* IndexProducer * IndexProducer::_pInstance=IndexProducer::getInstance("/home/ubuntu/projectC++/data/Dictionary"); */

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

void IndexProducer::createIndex()
{
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
            /* itIndex->second.insert(distance(_dict.begin(),it)-1); */ 
            /* cout<<"333"<<endl; */
        }
    }
}

void IndexProducer::store(const char *filepath)
{
    //存储到data文件夹里面，文件名字为Index
    string indexFile(filepath);
    indexFile.append("Index");
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
}
void IndexProducer::init()
{
    read();
    createIndex();
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


