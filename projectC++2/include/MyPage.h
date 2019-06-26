#pragma once
#include <string>
#include <unordered_map>
using std::string;
using std::unordered_map;
namespace  wd
{

class MyPage
{
public:
    void parse(const string &);//将webPage里面的内容分离出来
    string getSubStr(const string &,int &,const string &,const string &);//获取里面的子串内容
    void createWordFreMap();//生成词频map
    
    int getDocid()const 
    {
        return  _docid;
    }
    const string& getTitle()const{
        return _title;
    }
    const string& getLink()const{
        return _link;
    }
    const string& getDescription()const{
        return _description;
    }
    const string& getContent()const{
        return _content;
    }
    unordered_map<string , int > & getWordFreMap()
    {
        return _wordFreMap;
    }
private:
    int _docid;
    string _title;
    string _link;
    string _description;
    string _content;
    unordered_map<string ,int > _wordFreMap; 
};

}//end of namespace wd
