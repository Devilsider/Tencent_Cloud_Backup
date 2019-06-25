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
private:
    int _docid;
    string _title;
    string _link;
    string _description;
    string _content;
};

}//end of namespace wd
