#include "MyDict.h"
using std::ofstream;
using std::ifstream;
using std::stringstream;
using std::cout;
using std::endl;

namespace wd
{
MyDict * MyDict::_pInstance=MyDict::getInstance();
void MyDict::init(const string & filepath)
{
    //初始化路径
    _filepath=filepath;
    string dictPath(_filepath);
    string indexPath(_filepath);
    dictPath.append("Dictionary");
    indexPath.append("Index");
    
    ifstream ifsDict(dictPath);
    ifstream ifsIndex(indexPath);

    //从文件读入到_dict和_index
    string line;
    string word;
    int frequency;
    stringstream ss;
    while(getline(ifsDict,line))
    {
        //读_dict
        ss.clear();
        ss.str("");
        ss<<line;
        /* cout<<" "<<ss.str()<<endl;; */
        ss>>word;
        ss>>frequency;
        _dict.push_back(std::make_pair(word,frequency));
    }
    ifsDict.close();

    string idx;
    set<int> tmpIdxSet;
    int tmpNum;
    while(getline(ifsIndex,line))
    {
        //读Index
        tmpIdxSet.clear();
        ss.clear();
        ss.str("");
        ss<<line;
        /* cout<<" "<<ss.str()<<endl; */
        ss>>idx;
        _index.insert(std::make_pair(idx,tmpIdxSet));
        auto iter=_index.find(idx);
        if(iter==_index.end())
        {
            cout<<"read data error"<<endl;
            return;
        }
        while(ss>>tmpNum)
        {
            iter->second.insert(tmpNum);
        }
    }
    ifsIndex.clear();
}
void MyDict::showDict()
{
    for(auto &i:_dict)
    {
        cout<<i.first<<" "<<i.second<<endl;
    }
}

void MyDict::showIndex()
{
    for(auto &i:_index)
    {
        cout<<i.first<<" ";
        for(auto &c:i.second)
        {
            cout<<c<<" ";
        }
        cout<<endl;
    }
}

}//end of wd
