#pragma once
#include <string>
#include <unordered_map>
using std::string;
using std::unordered_map;

class MyWebPage
{
public:
    MyWebPage(int docid,
              const string &link,
              const string &title,
              const string &description,
              const string &content)
    :_docid(docid),
    _link(link),
    _title(title),
    _description(description),
    _content(content)
    {}

    int getDocid()const {
        return _docid;
    }
    const string &getLink()const{
        return _link;
    }
    const string &getTitle()const{
        return _title;
    }
    const string &getDescription()const{
        return _description;
    }
    const string &getContent()const{
        return _content;
    }
    unordered_map<string ,int > &getWordFreMap()
    {
        return _wordFreMap;
    }
private:
    int _docid;
    string _link;
    string _title;
    string _description;
    string _content;
    unordered_map<string ,int > _wordFreMap;
};

