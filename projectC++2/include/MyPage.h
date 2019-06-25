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
private:
    int _docid;
    string _title;
    string _link;
    string _description;
    string _content;
    map<string ,int > _wordFreMap;
};

}//end of namespace wd
