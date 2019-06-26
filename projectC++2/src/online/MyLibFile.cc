#include "MyLibFile.h"

#include <iostream>
using std::stringstream;
namespace wd
{
//初始化单例对象
MyLibFile * MyLibFile::_pInstance = MyLibFile::getInstance();

void MyLibFile::read(const string &webPageFile,const string &offset,const string &invertIndex)
{
    _webPageFile = webPageFile;
    ifstream ifsWebPage(_webPageFile);
    if(!ifsWebPage.is_open())
    {
        cout<<"open "<<webPageFile<<" error!"<<endl;
    }
    ifstream ifsOffset(offset);
    if(!ifsOffset.is_open())
    {
        cout<<"open "<<offset<<" error!"<<endl;
    }
    ifstream ifsInvertIndex(invertIndex);
    if(!ifsInvertIndex.is_open())
    {
        cout<<"open "<<invertIndex<<" error!"<<endl;
    }

    string line;
    while(getline(ifsOffset,line))
    {//读入偏移库
        stringstream ss;
        ss<<line;
        int docid;
        int offset;
        int len;
        ss>>docid>>offset>>len;
        auto iter = _offset.find(docid);
        if(iter == _offset.end())
        {//里面没有该网页
            _offset.insert(std::make_pair(docid,std::make_pair(offset,len)));
        }
    }

    while(getline(ifsInvertIndex,line))
    {
        stringstream ss;
        set<std::pair<int,double>> docAndWei;
        ss<<line;
        string word;
        ss>>word;
        while(!ss.fail())
        {
            int docid;
            double weight;
            ss>>docid>>weight;
            docAndWei.insert(std::make_pair(docid,weight));
        }
        auto iter = _invertIndex.find(word);
        if(iter == _invertIndex.end())
        {
            //找不到
            _invertIndex.insert(std::make_pair(word,docAndWei));
        }
    }
}
void MyLibFile::showOffset()
{
    for(auto & i:_offset)
    {
        cout<<i.first<<" "<<i.second.first<<" "<<i.second.second<<endl;
    }
}
void MyLibFile::showInvertIndex()
{
    for(auto &i:_invertIndex)
    {
        cout<<i.first<<" ";
        for(auto &c :i.second)
        {
            cout<<c.first<<" "<<c.second<<" ";
        }
        cout<<endl;
    }
}

}//end of wd

