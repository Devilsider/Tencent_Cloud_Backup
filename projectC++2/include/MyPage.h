#pragma once
#include <string>
#include <map>
using std::string;
using std::map;
namespace  wd
{

class MyPage
{
public:
    void parse(const string &);//将webPage里面的内容分离出来
    string getSubStr(const string &,int &,const string &,const string &);//获取里面的子串内容
private:
    int _docid;
    string _title;
    string _link;
    string _description;
    string _content;
    map<string ,int > _wordFreMap;
};

}//end of namespace wd
